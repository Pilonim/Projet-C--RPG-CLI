//
// Created by jonat on 16/10/2021.
//
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifndef PROJET_C___JEU_2D_MAP_H
#define PROJET_C___JEU_2D_MAP_H


void shuffle(int *array, size_t n);
int **mapGen(int height, int width, int *npc, int npcSize);
int** initMap(int width, int height, int stage);
#endif //PROJET_C___JEU_2D_MAP_H
