cmake_minimum_required(VERSION 3.30)
project(test2_practice_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(test2_practice_3 main.cpp
        UI.cpp
        UI.h
        Controller.cpp
        Controller.h
        HospitalDepartment.cpp
        HospitalDepartment.h)
