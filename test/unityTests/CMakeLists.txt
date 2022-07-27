set(CMOCK_PATH ../../cmock)

add_subdirectory(mocks)

add_executable(LedDriverTests 
  LedDriverTest.c 
)

target_link_libraries(LedDriverTests
  LedDriver
  Unity
  Mocks
)

add_executable(FlashTests
  FlashTest.c 
  ../../build/mocks/MockIO.c
)

target_link_libraries(FlashTests
  Flash
  Unity
  cmock
)

add_library(Unity STATIC
  ../../Unity/src/unity.c
)

target_include_directories(Unity PUBLIC
  ../../Unity/src
)

add_library(cmock
    ${CMOCK_PATH}/src/cmock.c
    ${CMOCK_PATH}/src/cmock.h
    ${CMOCK_PATH}/src/cmock_internals.h
)

target_include_directories(cmock PUBLIC
../../build/mocks
../../Unity/src
${CMOCK_PATH}/src/
)

add_test(
    NAME LedDriverTests
    COMMAND LedDriverTests
)

add_test(
    NAME FlashTests
    COMMAND FlashTests
)