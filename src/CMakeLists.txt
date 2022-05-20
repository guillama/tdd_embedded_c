cmake_minimum_required(VERSION 3.11)

project(LightScheduler)

add_library(LedDriver STATIC
    LedDriver.c
    LedDriver_helpers.c
)

add_library(LightScheduler STATIC
    LightControllerSpy.cpp
    LightScheduler.cpp
    FakeTimeService.cpp
    RandomMinute.c
    FakeRandomMinute.cpp
    FormatOutputSpy.cpp
    CircularBuffer.c
    Utils.c
)

target_include_directories(LedDriver PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)

target_include_directories(LightScheduler PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)