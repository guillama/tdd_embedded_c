cmake_minimum_required(VERSION 3.11)

project(LedDriverTests)

add_subdirectory(mocks)

add_executable(LedDriverTests LedDriverTest.c)
add_executable(ModuleTest ModuleTest.cpp)

target_link_libraries(LedDriverTests
LedDriver
Unity
Mocks)

target_link_libraries(ModuleTest
LedDriver
CppUTest
CppUTestExt
)

add_library(Unity STATIC
  ../Unity/src/unity.c
)

# add_library(CppUTest STATIC
#   ../cpputest/src/CppUTest/UTest.cpp
# )

target_include_directories(Unity PUBLIC
  ../Unity/src
)

include_directories(CppUTest PUBLIC
  ../cpputest/include
)

link_directories(CppUTest PUBLIC
  ../cpputest/Lib
)

add_test(
    NAME LedDriverTests
    COMMAND LedDriverTests
)

add_test(
    NAME ModuleTest
    COMMAND ModuleTest
)