cmake_minimum_required(VERSION 3.30)
project(mah_jong C)

set(CMAKE_C_STANDARD 17)

add_executable(mah_jong src/main.c
        src/game.c
        src/checks.c
        include/checks.h
        include/common.h
        src/common.c
        include/game.h
        src/ting_check.c
        include/ting_check.h
)
