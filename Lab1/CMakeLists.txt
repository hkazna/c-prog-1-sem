cmake_minimum_required(VERSION 3.29)
project(op_lab1 C)

set(CMAKE_C_STANDARD 11)

add_executable(op_lab1 main.c
        Actions.h
        Actions.c)