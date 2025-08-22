cmake_minimum_required(VERSION 3.30)
project(test1_oop_ex1)

set(CMAKE_CXX_STANDARD 20)

add_executable(test1_oop_ex1 main.cpp
        car.h
        Repository.cpp
        Repository.h
        Service.cpp
        Service.h
        UI.cpp
        UI.h
        car.cpp
        tests.cpp)
