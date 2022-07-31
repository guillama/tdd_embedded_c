set(CMOCK_PATH ../../cmock)
set(UNITY_PATH ../../Unity)

add_subdirectory(mocks)

add_executable(LedDriverTests 
  LedDriverTest.c 
)

target_link_libraries(LedDriverTests
  LedDriver
  Unity
  Mocks
)

add_test(
    NAME LedDriverTests
    COMMAND LedDriverTests
)