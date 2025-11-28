cmake_minimum_required(VERSION 4.0)
project(FMI C)

include(week3/CMakeLists.txt)
include(week4/CMakeLists.txt)
include(week5/CMakeLists.txt)
include(homework1/CMakeLists.txt)


set(CMAKE_C_STANDARD 11)

add_executable(FMI
        training/swapNums.c)
