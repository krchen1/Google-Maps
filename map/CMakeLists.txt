cmake_minimum_required(VERSION 3.26)
project(map C)

set(CMAKE_C_STANDARD 17)

add_library(library.c
        Street.c)

add_executable(map main.c Street.c Map.c Street.h Map.h
        Street.c)