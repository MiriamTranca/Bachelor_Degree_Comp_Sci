cmake_minimum_required(VERSION 3.30)
project(test2_practice2)

set(CMAKE_CXX_STANDARD 20)

add_executable(test2_practice2 main.cpp
        Appliance.cpp
        Appliance.h
        Service.cpp
        Service.h
        UI.cpp
        UI.h)
