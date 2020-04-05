cmake_minimum_required(VERSION 3.15)
project(texy)

set(CMAKE_CXX_STANDARD 20)

add_executable(texy main.cpp TexyInterpreter.cpp TexyInterpreter.hpp Commands.cpp Commands.hpp Global.hpp Variables.cpp Variables.hpp)