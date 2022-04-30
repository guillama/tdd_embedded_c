cmake_minimum_required(VERSION 3.11)

project(LightControllerSpy)

add_library(LedDriver STATIC
    LedDriver.c
    LedDriver_helpers.c
)

add_library(LightControllerSpy STATIC
    LightControllerSpy.cpp
    FakeTimeService.cpp
)

target_include_directories(LedDriver PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(LightControllerSpy PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)