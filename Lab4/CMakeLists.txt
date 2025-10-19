cmake_minimum_required(VERSION 3.29)
project(4oplab C)

set(CMAKE_C_STANDARD 17)

set(ZLIB_ROOT "C:/Users/user/Desktop/zlib")
set(PNG_ROOT "C:/Users/user/Desktop/libpng-libpng16")

find_package(ZLIB REQUIRED)
find_package(PNG REQUIRED)

include_directories(${ZLIB_INCLUDE_DIR} ${PNG_INCLUDE_DIRS})
link_directories(${ZLIB_LIBRARY} ${PNG_LIBRARIES})

add_executable(4lab_op main.c
        color_to_color.h
        color_to_color.c
        write_to_the_file.h
        write_to_the_file.c
        open_the_file.h
        open_the_file.c
        convertation.h
        convertation.c)

target_link_libraries(4lab_op PRIVATE PNG::PNG ZLIB::ZLIB)