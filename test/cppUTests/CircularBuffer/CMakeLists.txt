cmake_minimum_required(VERSION 3.11)

project(CircularBufferTests)

add_executable(CircularBufferTests 
CircularBufferPrintTest.cpp
AllTests.cpp)

target_link_libraries(CircularBufferTests
  LightScheduler
  CircularBuffer
  CppUTest
  CppUTestExt
)

include_directories(CppUTest PUBLIC
  ../cpputest/include
  ../cpputest/Lib
)

add_test(
    NAME CircularBufferTests
    COMMAND CircularBufferTests
)