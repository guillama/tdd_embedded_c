cmake_minimum_required(VERSION 3.11)

project(LightScheduler)

add_library(LightScheduler STATIC
    LightControllerSpy.cpp
    LightScheduler.cpp
    FakeTimeService.cpp
    RandomMinute.c
    FakeRandomMinute.cpp
    FormatOutputSpy.cpp
)

target_include_directories(LightScheduler PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)