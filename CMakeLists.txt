cmake_minimum_required(VERSION 3.19)
project(NeuralNetworkC C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(rso-mnist
        src/main.c
        src/Util.c
        src/Util.h src/structures.h src/main.c src/structures.c
        src/Calculs.c src/Calculs.h)
