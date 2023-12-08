cmake_minimum_required(VERSION 3.26)
project(Archive)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Archive
        Node_Graph.cpp
        Node_Graph.h
        main.cpp
        unittests.h)
