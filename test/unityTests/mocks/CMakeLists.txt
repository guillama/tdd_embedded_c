cmake_minimum_required(VERSION 3.11)

project(LedDriver)

add_library(Mocks STATIC
    RuntimeErrorStub.c
)

#add_executable(Mocks ${Sources})