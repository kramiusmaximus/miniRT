cmake_minimum_required(VERSION 3.17)
project(miniRT)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

file(GLOB LIBRARIES
        mlx/libmlx.a)

file(GLOB SOURCES
        srcs/*.c
        mlx/libmlx.a
        includes/*.h
        )
add_executable(miniRT ${SOURCES} main.c)
target_link_libraries(miniRT ${LIBRARIES})
target_link_libraries(miniRT /Users/markartyukh/Desktop/code/pfelipa/miniRT)
target_link_libraries(miniRT "-framework OpenGL" "-framework AppKit")

