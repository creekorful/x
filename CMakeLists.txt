cmake_minimum_required(VERSION 3.17)
project(x C)

set(CMAKE_C_STANDARD 11)

add_executable(x_test tests/test.c src/operation.h src/operation.c)

add_executable(x src/main.c src/operation.h src/operation.c)