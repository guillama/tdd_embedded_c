cmake_minimum_required(VERSION 3.11)

project(LedDriverTests)

add_subdirectory(mocks)

add_executable(LedDriverTests LedDriverTest.c)

target_link_libraries(LedDriverTests
  LedDriver
  Unity
  Mocks
)

add_library(Unity STATIC
  ../../Unity/src/unity.c
)

target_include_directories(Unity PUBLIC
  ../../Unity/src
)

add_test(
    NAME LedDriverTests
    COMMAND LedDriverTests
)