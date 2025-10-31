cmake_minimum_required(VERSION 4.0)
project(FMI C)

include(week3/CMakeLists.txt)
include(week4/CMakeLists.txt)


set(CMAKE_C_STANDARD 11)

add_executable(FMI
        week2/problems.c
        week3
        week4)
