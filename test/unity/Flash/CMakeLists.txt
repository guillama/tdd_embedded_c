add_executable(FlashTests
  FlashTest.c
  ${CMOCK_PATH}/lib/build/cmock/MockIO.c
)

target_link_libraries(FlashTests
  Flash
  Unity
  cmock
)

target_include_directories(FlashTests PUBLIC
  ${UNITY_PATH}/src
  ${CMOCK_PATH}/lib/build/cmock
)

add_test(
    NAME FlashTests
    COMMAND FlashTests
)
