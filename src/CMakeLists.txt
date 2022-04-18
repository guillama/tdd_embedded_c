cmake_minimum_required(VERSION 3.11)

project(LedDriver)

add_library(LedDriver STATIC
    LedDriver.c
    LedDriver_helpers.c
)

target_include_directories(LedDriver PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)