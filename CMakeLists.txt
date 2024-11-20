cmake_minimum_required(VERSION 3.29)
project(Codigo-Hamming-P3)

set(CMAKE_CXX_STANDARD 20)

add_executable(Hamming main.cpp
        utilities.h
        utilities.cpp
        hamming_generation.h
        hamming_generation.cpp
        error_handling.h
        error_handling.cpp
)
