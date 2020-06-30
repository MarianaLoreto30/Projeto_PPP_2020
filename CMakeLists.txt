cmake_minimum_required(VERSION 3.16)
project(Projeto C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-Wall -Wextra")

add_executable(Projeto main.c listas.h listas.c)