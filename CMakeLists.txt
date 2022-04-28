cmake_minimum_required(VERSION 3.16)
project(smash)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

add_executable(Commands.cpp signals.cpp smash.cpp Commands.h signals.h)