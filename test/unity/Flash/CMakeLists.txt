add_custom_command(
  COMMENT "Generating mocks headers"
  OUTPUT ${CMAKE_SOURCE_DIR}/mocks/MockIO.c
  COMMAND ruby ${CMOCK_PATH}/lib/cmock.rb
  ARGS ${CMAKE_SOURCE_DIR}/src/Flash/IO.h
  WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

add_executable(FlashTests
  FlashTest.c
  ${CMAKE_SOURCE_DIR}/mocks/MockIO.c
)

target_link_libraries(FlashTests
  Flash
  Unity
  cmock
)

target_include_directories(FlashTests PUBLIC
  ${UNITY_PATH}/src
  ${CMAKE_SOURCE_DIR}/mocks
)

add_test(
    NAME FlashTests
    COMMAND FlashTests
)

add_dependencies(FlashTests cmock)
