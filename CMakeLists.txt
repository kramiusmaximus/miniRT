cmake_minimum_required(VERSION 3.17)
project(miniRT)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes libft/includes mlx)

file(GLOB LIBRARIES
        libft/libft.a
        mlx/libmlx.a
        )
find_library(
        MLX
        libmlx.dylib
        PATHS
        /Users/pfelipa/Desktop/pfelipa/miniRT)

file(GLOB SOURCES
        srcs/*.c
        srcs/*/*.c
        includes/*.h
        libft/includes/*.h
        mlx/*.h
        )
add_executable(miniRT ${SOURCES} )
target_link_libraries(miniRT ${LIBRARIES})

#shkola : /Users/pfelipa/Desktop/pfelipa/miniRT
#home : /Users/markartyukh/Desktop/code/pfelipa/miniRT
target_link_libraries(miniRT "-framework OpenGL" "-framework AppKit")
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(miniRT Threads::Threads)