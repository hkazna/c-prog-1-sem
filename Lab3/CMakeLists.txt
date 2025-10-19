cmake_minimum_required(VERSION 3.29)
project(src C)

set(CMAKE_C_STANDARD 17)

add_executable(src main.c
        parsing.h
        parsing.c
        applying_operations.h
        applying_operations.c
        calculation.h
        calculation.c
        is_unary_operation.h
        is_unary_operation.c)