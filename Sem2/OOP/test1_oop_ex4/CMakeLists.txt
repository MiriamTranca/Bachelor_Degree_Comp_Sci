cmake_minimum_required(VERSION 3.30)
project(test1_oop_ex4)

set(CMAKE_CXX_STANDARD 20)

add_executable(test1_oop_ex4 main.cpp
        Patient.cpp
        Patient.h
        Repo.cpp
        Repo.h
        Service.cpp
        Service.h
        Ui.cpp
        Ui.h
        Tests.cpp
        Tests.h
)
