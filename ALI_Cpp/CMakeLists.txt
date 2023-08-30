cmake_minimum_required(VERSION 3.23)
project(project4_CPP_ALI)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project4_CPP_ALI
        ALI.cpp
        ALI.h
        Hardware.cpp
        Hardware.h
        Instruction.cpp
        Instruction.h
        main.cpp
        subclasses.cpp
        subclasses.h)
