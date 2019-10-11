/*
 *  nextpnr -- Next Generation Place and Route
 *
 *  Copyright (C) 2018  David Shah <david@symbioticeda.com>
 *
 *  Permission to use, copy, modify, and/or distribute this software for any
 *  purpose with or without fee is hereby granted, provided that the above
 *  copyright notice and this permission notice appear in all copies.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 *  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 *  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 *  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 *  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 *  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifndef ECP5_GFX_H
#define ECP5_GFX_H

#include "nextpnr.h"

NEXTPNR_NAMESPACE_BEGIN

const float switchbox_x1 = 0.51;
const float switchbox_x2 = 0.90;
const float switchbox_y1 = 0.51;
const float switchbox_y2 = 0.90;

const float slice_x1 = 0.92;
const float slice_x2 = 0.94;
const float slice_y1 = 0.71;
const float slice_y2 = 0.745;
const float slice_pitch = 0.0374;

const float io_cell_v_x1 = 0.76;
const float io_cell_v_x2 = 0.95;
const float io_cell_v_y1 = 0.05;
const float io_cell_v_y2 = 0.15;
const float io_cell_v_pitch = 0.125;

const float io_cell_h_x1 = 0.05;
const float io_cell_h_x2 = 0.14;
const float io_cell_h_y1 = 0.05;
const float io_cell_h_y2 = 0.24;
const float io_cell_h_pitch = 0.125;

enum GfxTileWireId
{
    TILE_WIRE_NONE,

    TILE_WIRE_D7_SLICE,
    TILE_WIRE_C7_SLICE,
    TILE_WIRE_B7_SLICE,
    TILE_WIRE_A7_SLICE,
    TILE_WIRE_D6_SLICE,
    TILE_WIRE_C6_SLICE,
    TILE_WIRE_B6_SLICE,
    TILE_WIRE_A6_SLICE,
    TILE_WIRE_DI7_SLICE,
    TILE_WIRE_DI6_SLICE,
    TILE_WIRE_M7_SLICE,
    TILE_WIRE_M6_SLICE,
    TILE_WIRE_FXBD_SLICE,
    TILE_WIRE_FXAD_SLICE,
    TILE_WIRE_DUMMY_001,
    TILE_WIRE_DUMMY_002,
    TILE_WIRE_CE3_SLICE,
    TILE_WIRE_LSR3_SLICE,
    TILE_WIRE_CLK3_SLICE,
    
    TILE_WIRE_DUMMY_003,
    TILE_WIRE_DUMMY_004,
    TILE_WIRE_DUMMY_005,

    TILE_WIRE_D5_SLICE,
    TILE_WIRE_C5_SLICE,
    TILE_WIRE_B5_SLICE,
    TILE_WIRE_A5_SLICE,
    TILE_WIRE_D4_SLICE,
    TILE_WIRE_C4_SLICE,
    TILE_WIRE_B4_SLICE,
    TILE_WIRE_A4_SLICE,
    TILE_WIRE_DI5_SLICE,
    TILE_WIRE_DI4_SLICE,
    TILE_WIRE_M5_SLICE,
    TILE_WIRE_M4_SLICE,
    TILE_WIRE_FXBC_SLICE,
    TILE_WIRE_FXAC_SLICE,
    TILE_WIRE_DUMMY_006,
    TILE_WIRE_DUMMY_007,
    TILE_WIRE_CE2_SLICE,
    TILE_WIRE_LSR2_SLICE,
    TILE_WIRE_CLK2_SLICE,

    TILE_WIRE_DUMMY_008,
    TILE_WIRE_DUMMY_009,
    TILE_WIRE_DUMMY_010,

    TILE_WIRE_D3_SLICE,
    TILE_WIRE_C3_SLICE,
    TILE_WIRE_B3_SLICE,
    TILE_WIRE_A3_SLICE,
    TILE_WIRE_D2_SLICE,
    TILE_WIRE_C2_SLICE,
    TILE_WIRE_B2_SLICE,
    TILE_WIRE_A2_SLICE,
    TILE_WIRE_DI3_SLICE,
    TILE_WIRE_DI2_SLICE,
    TILE_WIRE_M3_SLICE,
    TILE_WIRE_M2_SLICE,
    TILE_WIRE_FXBB_SLICE,
    TILE_WIRE_FXAB_SLICE,
    TILE_WIRE_WRE1_SLICE,
    TILE_WIRE_WCK1_SLICE,
    TILE_WIRE_CE1_SLICE,
    TILE_WIRE_LSR1_SLICE,
    TILE_WIRE_CLK1_SLICE,

    TILE_WIRE_DUMMY_011,
    TILE_WIRE_DUMMY_012,
    TILE_WIRE_DUMMY_013,

    TILE_WIRE_D1_SLICE,
    TILE_WIRE_C1_SLICE,
    TILE_WIRE_B1_SLICE,
    TILE_WIRE_A1_SLICE,
    TILE_WIRE_D0_SLICE,
    TILE_WIRE_C0_SLICE,
    TILE_WIRE_B0_SLICE,
    TILE_WIRE_A0_SLICE,
    TILE_WIRE_DI1_SLICE,
    TILE_WIRE_DI0_SLICE,
    TILE_WIRE_M1_SLICE,
    TILE_WIRE_M0_SLICE,
    TILE_WIRE_FXBA_SLICE,
    TILE_WIRE_FXAA_SLICE,
    TILE_WIRE_WRE0_SLICE,
    TILE_WIRE_WCK0_SLICE,
    TILE_WIRE_CE0_SLICE,
    TILE_WIRE_LSR0_SLICE,
    TILE_WIRE_CLK0_SLICE,

    TILE_WIRE_FCO_SLICE,
    TILE_WIRE_FCID_SLICE,
    TILE_WIRE_FCOC_SLICE,
    TILE_WIRE_FCIC_SLICE,
    TILE_WIRE_FCOB_SLICE,
    TILE_WIRE_FCIB_SLICE,
    TILE_WIRE_FCOA_SLICE,
    TILE_WIRE_FCI_SLICE,

    TILE_WIRE_DUMMY_100,
    TILE_WIRE_DUMMY_101,
    TILE_WIRE_DUMMY_102,
    TILE_WIRE_DUMMY_103,
    TILE_WIRE_DUMMY_104,
    TILE_WIRE_DUMMY_105,
    TILE_WIRE_DUMMY_106,
    TILE_WIRE_DUMMY_107,
    TILE_WIRE_DUMMY_108,
    TILE_WIRE_DUMMY_109,
    TILE_WIRE_DUMMY_110,
    TILE_WIRE_DUMMY_111,
    TILE_WIRE_DUMMY_112,
    TILE_WIRE_FXD_SLICE,
    TILE_WIRE_F7_SLICE,
    TILE_WIRE_Q7_SLICE,
    TILE_WIRE_Q6_SLICE,
    TILE_WIRE_F6_SLICE,
    TILE_WIRE_F5D_SLICE,
    
    TILE_WIRE_DUMMY_113,
    TILE_WIRE_DUMMY_114,
    TILE_WIRE_DUMMY_115,

    TILE_WIRE_WDO3C_SLICE,
    TILE_WIRE_WDO2C_SLICE,
    TILE_WIRE_WDO1C_SLICE,
    TILE_WIRE_WDO0C_SLICE,
    TILE_WIRE_DUMMY_200,
    TILE_WIRE_WADO3C_SLICE,
    TILE_WIRE_WADO2C_SLICE,
    TILE_WIRE_WADO1C_SLICE,
    TILE_WIRE_WADO0C_SLICE,
    TILE_WIRE_DUMMY_201,
    TILE_WIRE_DUMMY_202,
    TILE_WIRE_DUMMY_203,
    TILE_WIRE_DUMMY_204,
    TILE_WIRE_FXC_SLICE,
    TILE_WIRE_F5_SLICE,
    TILE_WIRE_Q5_SLICE,
    TILE_WIRE_Q4_SLICE,
    TILE_WIRE_F4_SLICE,
    TILE_WIRE_F5C_SLICE,

    TILE_WIRE_DUMMY_213,
    TILE_WIRE_DUMMY_214,
    TILE_WIRE_DUMMY_215,

    TILE_WIRE_DUMMY_300,
    TILE_WIRE_DUMMY_301,
    TILE_WIRE_WD1B_SLICE,
    TILE_WIRE_WD0B_SLICE,
    TILE_WIRE_DUMMY_302,
    TILE_WIRE_WAD3B_SLICE,
    TILE_WIRE_WAD2B_SLICE,
    TILE_WIRE_WAD1B_SLICE,
    TILE_WIRE_WAD0B_SLICE,
    TILE_WIRE_DUMMY_303,
    TILE_WIRE_DUMMY_304,
    TILE_WIRE_DUMMY_305,
    TILE_WIRE_DUMMY_306,
    TILE_WIRE_FXB_SLICE,
    TILE_WIRE_F3_SLICE,
    TILE_WIRE_Q3_SLICE,
    TILE_WIRE_Q2_SLICE,
    TILE_WIRE_F2_SLICE,
    TILE_WIRE_F5B_SLICE,    

    TILE_WIRE_DUMMY_313,
    TILE_WIRE_DUMMY_314,
    TILE_WIRE_DUMMY_315,

    TILE_WIRE_DUMMY_400,
    TILE_WIRE_DUMMY_401,
    TILE_WIRE_WD1A_SLICE,
    TILE_WIRE_WD0A_SLICE,
    TILE_WIRE_DUMMY_402,
    TILE_WIRE_WAD3A_SLICE,
    TILE_WIRE_WAD2A_SLICE,
    TILE_WIRE_WAD1A_SLICE,
    TILE_WIRE_WAD0A_SLICE,
    TILE_WIRE_DUMMY_403,
    TILE_WIRE_DUMMY_404,
    TILE_WIRE_DUMMY_405,
    TILE_WIRE_DUMMY_406,
    TILE_WIRE_FXA_SLICE,
    TILE_WIRE_F1_SLICE,
    TILE_WIRE_Q1_SLICE,
    TILE_WIRE_Q0_SLICE,
    TILE_WIRE_F0_SLICE,
    TILE_WIRE_F5A_SLICE,


    TILE_WIRE_LSR1,
    TILE_WIRE_LSR0,
    TILE_WIRE_CLK1,
    TILE_WIRE_CLK0,
    TILE_WIRE_DUMMY_500,
    TILE_WIRE_FCO,
    TILE_WIRE_D7,
    TILE_WIRE_C7,
    TILE_WIRE_B7,
    TILE_WIRE_A7,
    TILE_WIRE_D6,
    TILE_WIRE_C6,
    TILE_WIRE_B6,
    TILE_WIRE_A6,
    TILE_WIRE_DI7,
    TILE_WIRE_DI6,
    TILE_WIRE_M7,
    TILE_WIRE_M6,
    TILE_WIRE_FXBD,
    TILE_WIRE_FXAD,
    TILE_WIRE_DUMMY_501,
    TILE_WIRE_DUMMY_502,
    TILE_WIRE_CE3,
    TILE_WIRE_DUMMY_503,
    TILE_WIRE_DUMMY_504,    

    TILE_WIRE_DUMMY_505,
    TILE_WIRE_DUMMY_506,
    TILE_WIRE_DUMMY_507,

    TILE_WIRE_D5,
    TILE_WIRE_C5,
    TILE_WIRE_B5,
    TILE_WIRE_A5,
    TILE_WIRE_D4,
    TILE_WIRE_C4,
    TILE_WIRE_B4,
    TILE_WIRE_A4,    
    TILE_WIRE_DI5,
    TILE_WIRE_DI4,
    TILE_WIRE_M5,
    TILE_WIRE_M4,
    TILE_WIRE_FXBC,
    TILE_WIRE_FXAC,
    TILE_WIRE_DUMMY_508,
    TILE_WIRE_DUMMY_509,
    TILE_WIRE_CE2,
    TILE_WIRE_DUMMY_510,
    TILE_WIRE_DUMMY_511,    


};

NEXTPNR_NAMESPACE_END

#endif
