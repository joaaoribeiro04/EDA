cmake_minimum_required(VERSION 3.24)
project(EDA C)

set(CMAKE_C_STANDARD 11)

add_executable(EDA main.c meio.c gestor.h dlist.h gestor.c dlist.c cliente.h cliente.c utils.h utils.c grafo.c grafo.h menu.h)

target_link_libraries(EDA m)
