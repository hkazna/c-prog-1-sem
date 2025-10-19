cmake_minimum_required(VERSION 3.29)
project(src C)

set(CMAKE_C_STANDARD 17)

add_executable(src main.c
        print.h
        print.c
        init_int128.h
        init_int128.c
        formatting.c
        formatting.c
        format.h)