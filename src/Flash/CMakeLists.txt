cmake_minimum_required(VERSION 3.11)

project(LightScheduler)

add_library(Flash STATIC
    Flash.c
    FakeMicroTime.c
)

target_include_directories(Flash PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)