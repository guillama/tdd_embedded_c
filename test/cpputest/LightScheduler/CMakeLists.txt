cmake_minimum_required(VERSION 3.11)

project(LightSchedulerTests)

add_executable(LightSchedulerTests 
LightControllerSpyTest.cpp
LightSchedulerTest.cpp
FakeTimeServiceTest.cpp
LightSchedulerInitAndCleanupTest.cpp
RandomMinuteTest.cpp
LightSchedulerRandomizeTest.cpp
FormatOutputSpyTest.cpp
AllTests.cpp)

target_link_libraries(LightSchedulerTests
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
    NAME LightSchedulerTests
    COMMAND LightSchedulerTests
)