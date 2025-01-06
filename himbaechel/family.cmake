set(HIMBAECHEL_UARCHES "xilinx")
foreach(uarch ${HIMBAECHEL_UARCHES})
	add_subdirectory(${family}/uarch/${uarch})
    aux_source_directory(${family}/uarch/${uarch} HM_UARCH_FILES)
    foreach(target ${family_targets})
        target_sources(${target} PRIVATE ${HM_UARCH_FILES})
    endforeach()
    if (BUILD_TESTS)
        foreach(target ${family_test_targets})
            aux_source_directory(${family}/uarch/${uarch}/tests/ HM_UARCH_TEST_FILES)
            target_sources(${target} PRIVATE ${HM_UARCH_TEST_FILES})
        endforeach()
    endif()
endforeach(uarch)
