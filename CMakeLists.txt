cmake_minimum_required(VERSION 3.19)
project(NeuralNetworkC C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(rso-mnist
        src/main.c
        src/Util.c src/Util.h
        src/structures.h src/structures.c
        src/calculs.c src/calculs.h
        src/Util.c src/Util.h
        src/functionsIO.c src/functionsIO.h
        src/fonctionsRso.c src/fonctionsRso.h)
target_link_libraries(rso-mnist m)