cmake_minimum_required(VERSION 3.11)

project(tdd_embedded_c)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Werror -g -O0")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMOCK_PATH ${CMAKE_CURRENT_LIST_DIR}/cmock)
set(UNITY_PATH ${CMAKE_CURRENT_LIST_DIR}/Unity)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(Unity)
add_subdirectory(cpputest)
