cmake_minimum_required(VERSION 3.17)
project(x C)

set(CMAKE_C_STANDARD 11)

add_executable(x main.c operation.h operation.c)