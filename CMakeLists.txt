cmake_minimum_required(VERSION 3.15)
project(text-machine)

set(CMAKE_CXX_STANDARD 20)

add_executable(text-machine main.cpp Interpreter.cpp Interpreter.hpp Commands.cpp Commands.hpp Global.hpp Variables.cpp Variables.hpp)