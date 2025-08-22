cmake_minimum_required(VERSION 3.30)
project(test1_oop_ex2)

set(CMAKE_CXX_STANDARD 20)

add_executable(test1_oop_ex2 main.cpp
        school.cpp
        school.h
        repo.cpp
        repo.h
        service.cpp
        service.h
        Ui.cpp
        Ui.h
        test.cpp)
