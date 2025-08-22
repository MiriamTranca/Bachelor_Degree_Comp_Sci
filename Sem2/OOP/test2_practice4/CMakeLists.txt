cmake_minimum_required(VERSION 3.30)
project(test2_practice4)

set(CMAKE_CXX_STANDARD 20)

add_executable(test2_practice4 main.cpp
        Building.cpp
        Building.h
        Controller.cpp
        Controller.h
        UI.cpp
        UI.h)
