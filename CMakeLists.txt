cmake_minimum_required(VERSION 3.28)
project(inf_project)

set(CMAKE_CXX_STANDARD 17)

add_executable(inf_project main.cpp
        Source/GameObject.cpp
        Headers/GameObject.h
        Source/TimeSpace.cpp
        Headers/TimeSpace.h
)
