cmake_minimum_required(VERSION 3.11)

project(CircularBuffer)

add_library(CircularBuffer STATIC
    CircularBuffer.c
    Utils.c
)

target_include_directories(CircularBuffer PUBLIC
  ${CMAKE_CURRENT_LIST_DIR}
)