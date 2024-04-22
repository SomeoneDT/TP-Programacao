cmake_minimum_required(VERSION 3.25)
project(PTP C)

set(CMAKE_C_STANDARD 99)

include_directories(.)

add_executable(PTP
        main.c
        menu.c
        sistemas.h
        utils.c
        estacoes.c
        linhas.c course.c utils.h linhas.h estacoes.h menu.h course.h)
