cmake_minimum_required(VERSION 3.11)

project(LedDriverTests)

add_subdirectory(mocks)

add_executable(LedDriverTests LedDriverTest.c)

add_executable(LightControllerSpyTest 
LightControllerSpyTest.cpp
LightSchedulerTest.cpp
FakeTimeServiceTest.cpp)

target_link_libraries(LedDriverTests
  LedDriver
  Unity
  Mocks
)

target_link_libraries(LightControllerSpyTest
  LightControllerSpy
  CppUTest
  CppUTestExt
)

add_library(Unity STATIC
  ../Unity/src/unity.c
)

target_include_directories(Unity PUBLIC
  ../Unity/src
)

include_directories(CppUTest PUBLIC
  ../cpputest/include
  ../cpputest/Lib
)

add_test(
    NAME LedDriverTests
    COMMAND LedDriverTests
)

add_test(
    NAME LightControllerSpyTest
    COMMAND LightControllerSpyTest
)