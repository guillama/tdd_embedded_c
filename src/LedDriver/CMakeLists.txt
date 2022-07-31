add_library(LedDriver STATIC
    LedDriver.c
    LedDriver_helpers.c
)

target_include_directories(LedDriver PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_compile_options(LedDriver PRIVATE --coverage)
target_link_options(LedDriver PUBLIC --coverage)

include(Coverage)
CleanCoverage(LedDriver)