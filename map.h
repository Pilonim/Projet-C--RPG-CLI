//
// Created by jonat on 16/10/2021.
//

#ifndef PROJET_C___JEU_2D_MAP_H
#define PROJET_C___JEU_2D_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
void shuffle(int *array, size_t n);
int **mapGen(int height, int width, int *npc, int npcSize, int ***diedNpcs, int *nbDiedNpcs, int stage, int *currentPos);
int **initMap(int width, int height, int stage, int ***diedNpcs, int *nbDiedNpcs, Mob *mobs, int *nbMobs, int *currentPos);
int **initMap2(Game **game, int stage);
int **mapGen2(Game **game, int stage, int *npc, int npcSize);
#endif //PROJET_C___JEU_2D_MAP_H
