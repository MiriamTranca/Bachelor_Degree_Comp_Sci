cmake_minimum_required(VERSION 3.30)
project(test1_oop_ex3)

set(CMAKE_CXX_STANDARD 20)

add_executable(test1_oop_ex3 main.cpp
        Task.cpp
        Task.h
        Repo.cpp
        Repo.h
        Tests.cpp
        Tests.h
        Service.cpp
        Service.h
        Ui.cpp
        Ui.h)
