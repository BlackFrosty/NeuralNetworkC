cmake_minimum_required(VERSION 3.19)
project(NeuralNetworkC C)

set(CMAKE_C_STANDARD 11)

include_directories(src)

add_executable(NeuralNetworkC
        src/Bitmap.c
        src/Bitmap.h
        src/Couche.c
        src/Couche.h
        src/file_mgmt.c
        src/file_mgmt.h
        src/Iris.c
        src/Iris.h
        src/main.c
        src/Neurone.c
        src/Neurone.h
        src/PMC.c
        src/PMC.h
        src/Statistiques.c
        src/Statistiques.h
        src/Util.c
        src/Util.h src/structures.h src/main.c)
