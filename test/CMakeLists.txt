include(CTest)

add_subdirectory(unity)
add_subdirectory(cpputest)

include(Coverage)
AddCoverage(FlashTests)
AddCoverage(LedDriverTests)