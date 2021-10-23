cmake_minimum_required(VERSION 3.20)
project(Projet_C___Jeu_2D C)

set(CMAKE_C_STANDARD 11)

add_executable(Projet_C___Jeu_2D main.c map.c map.h move.c move.h mobs.c mobs.h character.c character.h struct.h farm.c farm.h fight.c fight.h)
