use std::{ptr::NonNull, time::Instant};

use colored::Colorize;

#[macro_use]
mod npnr;
mod partition;
mod route;

#[no_mangle]
pub extern "C" fn npnr_router_awooter(ctx: Option<NonNull<npnr::Context>>) -> bool {
    std::panic::catch_unwind(move || {
        let ctx: &mut npnr::Context = unsafe { ctx.expect("non-null context").as_mut() };
        route(ctx)
    })
    .unwrap_or_else(|x| {
        if let Ok(x) = x.downcast::<String>() {
            log_error!("caught panic: {}", x);
        }
        false
    })
}

type Arc = ((npnr::WireId, npnr::Loc), (npnr::WireId, npnr::Loc));

fn extract_arcs_from_nets(ctx: &npnr::Context, nets: npnr::Nets) -> Vec<Arc> {
    let mut arcs = vec![];
    for (name, net) in nets.iter() {
        let net = unsafe { net.as_mut().unwrap() };
        if net.is_global() {
            continue;
        }
        let port_ref = net.driver();
        let port_ref = unsafe { port_ref.as_ref().unwrap() };
        if let Some(cell) = port_ref.cell() {
            let source = cell.location();
            let source_wire = ctx.source_wire(net);

            for sink_ref in nets.users_by_name(*name).unwrap().iter() {
                let sink = sink_ref.cell().unwrap();
                let sink = sink.location();
                for sink_wire in ctx.sink_wires(net, *sink_ref) {
                    arcs.push(((source_wire, source), (sink_wire, sink)))
                }
            }
        }
    }
    arcs
}

fn route(ctx: &mut npnr::Context) -> bool {
    log_info!(
        "{}{}{}{}{}{} from Rust!\n",
        "A".red(),
        "w".green(),
        "o".yellow(),
        "o".blue(),
        "o".magenta(),
        "o".cyan()
    );
    log_info!(
        "Running on a {}x{} grid\n",
        ctx.grid_dim_x().to_string().bold(),
        ctx.grid_dim_y().to_string().bold(),
    );

    let wires = ctx.wires_leaking();
    log_info!("Found {} wires\n", wires.len().to_string().bold());

    let pips = ctx.pips_leaking();
    log_info!("Found {} pips\n", pips.len().to_string().bold());

    let nets = npnr::Nets::new(ctx);
    let nets_str = nets.len().to_string();
    log_info!("Found {} nets\n", nets_str.bold());

    let mut count = 0;
    for (name, net) in nets.iter() {
        let _src = ctx.source_wire(*net);
        let net = unsafe { net.as_mut().unwrap() };
        let users = nets.users_by_name(*name).unwrap().iter();
        for user in users {
            count += ctx.sink_wires(net, *user).len();
        }
    }

    log_info!("Found {} arcs\n", count.to_string().bold());

    let (name, net) = nets
        .iter()
        .max_by_key(|(name, net)| {
            let net = unsafe { net.as_mut().unwrap() };
            if net.is_global() {
                0
            } else {
                nets.users_by_name(**name)
                    .unwrap()
                    .iter()
                    .fold(0, |acc, sink| acc + ctx.sink_wires(net, *sink).len())
            }
        })
        .unwrap();

    let net = unsafe { net.as_mut().unwrap() };
    let count = nets
        .users_by_name(*name)
        .unwrap()
        .iter()
        .fold(0, |acc, sink| acc + ctx.sink_wires(net, *sink).len())
        .to_string();

    log_info!(
        "Highest non-global fanout net is {}\n",
        ctx.name_of(*name).to_str().unwrap().bold()
    );
    log_info!("  with {} arcs\n", count.bold());

    let mut x0 = 0;
    let mut y0 = 0;
    let mut x1 = 0;
    let mut y1 = 0;

    for sink in nets.users_by_name(*name).unwrap().iter() {
        let cell = sink.cell().unwrap().location();
        x0 = x0.min(cell.x);
        y0 = y0.min(cell.y);
        x1 = x1.max(cell.x);
        y1 = y1.max(cell.y);
    }

    let coords_min = format!("({}, {})", x0, y0);
    let coords_max = format!("({}, {})", x1, y1);
    log_info!(
        "  which spans from {} to {}\n",
        coords_min.bold(),
        coords_max.bold()
    );

    log_info!(
        "rayon reports {} threads available\n",
        rayon::current_num_threads().to_string().bold()
    );

    let start = Instant::now();

    let arcs = extract_arcs_from_nets(ctx, nets);

    let (x_part, y_part, ne, se, sw, nw) = partition::find_partition_point(
        ctx,
        &arcs[..],
        pips,
        0,
        ctx.grid_dim_x(),
        0,
        ctx.grid_dim_y(),
    );

    let time = Instant::now() - start;

    log_info!("Partitioning took {:.2}s\n", time.as_secs_f32());

    let mut invalid_arcs_in_ne = 0;
    let mut invalid_arcs_in_se = 0;
    let mut invalid_arcs_in_sw = 0;
    let mut invalid_arcs_in_nw = 0;

    for ((_, source), (_, sink)) in ne {
        if source.x > x_part || source.y > y_part || sink.x > x_part || sink.y > y_part {
            invalid_arcs_in_ne += 1;
        }
    }
    for ((_, source), (_, sink)) in se {
        if source.x < x_part || source.y > y_part || sink.x < x_part || sink.y > y_part {
            invalid_arcs_in_se += 1;
        }
    }
    for ((_, source), (_, sink)) in sw {
        if source.x < x_part || source.y < y_part || sink.x < x_part || sink.y < y_part {
            invalid_arcs_in_sw += 1;
        }
    }
    for ((_, source), (_, sink)) in nw {
        if source.x > x_part || source.y < y_part || sink.x > x_part || sink.y < y_part {
            invalid_arcs_in_nw += 1;
        }
    }

    if [
        invalid_arcs_in_ne,
        invalid_arcs_in_se,
        invalid_arcs_in_sw,
        invalid_arcs_in_nw,
    ]
    .into_iter()
    .all(|x| x == 0)
    {
        log_info!(
            "{}\n",
            "Found no arcs crossing partition boundaries.".green()
        );
    } else {
        println!("{}", "found arcs crossing partition boundaries!".yellow());
        println!("count in ne: {}", invalid_arcs_in_ne.to_string().bold());
        println!("count in se: {}", invalid_arcs_in_se.to_string().bold());
        println!("count in sw: {}", invalid_arcs_in_sw.to_string().bold());
        println!("count in nw: {}", invalid_arcs_in_nw.to_string().bold());
    }

    /*log_info!("=== level 2 NE:\n");
    let _ = find_partition_point(&ne, x_start, x, y_start, y);
    log_info!("=== level 2 SE:\n");
    let _ = find_partition_point(&se, x, x_finish, y_start, y);
    log_info!("=== level 2 SW:\n");
    let _ = find_partition_point(&sw, x, x_finish, y, y_finish);
    log_info!("=== level 2 NW:\n");
    let _ = find_partition_point(&nw, x_start, x, y, y_finish);*/

    true
}