cmake_minimum_required(VERSION 3.30)
project(test2_practice1)

set(CMAKE_CXX_STANDARD 20)

add_executable(test2_practice1 main.cpp
        person.h
        person.cpp
        ui.h
        ui.cpp
        MedicalAnalysis.cpp
        MedicalAnalysis.h
)
