add_executable(FlashTests
  FlashTest.c 
  ${CMAKE_BINARY_DIR}/cmock/MockIO.c
)

target_link_libraries(FlashTests
  Flash
  Unity
  cmock
)

target_include_directories(FlashTests PUBLIC
  ${UNITY_PATH}/src
  ${CMAKE_BINARY_DIR}/cmock
)

add_test(
    NAME FlashTests
    COMMAND FlashTests
)