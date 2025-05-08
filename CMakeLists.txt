cmake_minimum_required(VERSION 3.30)
project(mah_jong C)

set(CMAKE_C_STANDARD 17)

add_executable(mah_jong main.c
        game.c
        checks.c
        checks.h
        common.h
        common.c
)
