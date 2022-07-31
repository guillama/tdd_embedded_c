function(AddCoverage target)
    find_program(LCOV_PATH lcov REQUIRED)
    find_program(GENHTML_PATH genhtml REQUIRED)

    add_custom_target(coverage-${target}
        COMMENT "Running coverage for ${target}"
        COMMAND ${LCOV_PATH} -d . --zerocounters
        COMMAND $<TARGET_FILE:${target}>
        COMMAND ${LCOV_PATH} -d . --capture -o coverage.info
        COMMAND ${LCOV_PATH} -r coverage.info '/usr/include/*' -o filtered.info
        COMMAND ${GENHTML_PATH} -o coverage-${target} filtered.info --legend
        COMMAND rm -f coverage.info filetered.info
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endfunction()

function(CleanCoverage target)
    add_custom_command( TARGET ${target} PRE_BUILD
    COMMENT "Cleaning old coverage data for target ${target}"
    COMMAND find ${CMAKE_BINARY_DIR} -type f 
    -name '*.gcda' -exec rm {} +)
endfunction()