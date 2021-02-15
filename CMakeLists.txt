cmake_minimum_required(VERSION 3.17)
project(miniRT)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes)

file(GLOB LIBRARIES
        mlx/libmlx.a
        libft/libft.a
        )

file(GLOB SOURCES
        srcs/*.c
        srcs/*/*.c
        mlx/libmlx.a
        includes/*.h
        )
add_executable(miniRT ${SOURCES} main.c)
target_link_libraries(miniRT ${LIBRARIES})

#shkola : /Users/pfelipa/Desktop/pfelipa/miniRT
#home : /Users/markartyukh/Desktop/code/pfelipa/miniRT
target_link_libraries(miniRT /Users/pfelipa/Desktop/pfelipa/miniRT)
target_link_libraries(miniRT "-framework OpenGL" "-framework AppKit")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(miniRT Threads::Threads)