cmake_minimum_required(VERSION 3.20)
project(testoo C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_C___Jeu_2D sources/sources/main.c sources/sources/map.c sources/headers/map.h sources/sources/move.c sources/headers/move.h sources/sources/mobs.c sources/headers/mobs.h sources/sources/character.c sources/headers/character.h sources/headers/struct.h sources/sources/farm.c sources/headers/farm.h sources/sources/fight.c sources/headers/fight.h sources/sources/craft.c sources/headers/craft.h sources/sources/pnj.c sources/headers/pnj.h sources/sources/save.c sources/headers/save.h)
