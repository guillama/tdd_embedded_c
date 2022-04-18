cmake_minimum_required(VERSION 3.11)

project(LedDriver)

set(CMAKE_C_STANDARD 90)
set(CMAKE_C_FLAGS "-Wall -Werror")

# We declare a variable to select what to build set
set(CIBLE production CACHE STRING "What Should I Build?")

add_subdirectory(src)

if(CIBLE STREQUAL release)
# nothing to add
elseif(CIBLE STREQUAL test)
  message("Unit testing !")

  include(CTest)

  add_subdirectory(test)
  add_subdirectory(Unity)
else() 
  message(FATAL_ERROR "I don't know the CIBLE you gave me!")
endif()

# add_library(Unity STATIC
#   Unity/src/unity.c
# )

# target_include_directories(Unity PUBLIC
#   Unity/src
# )