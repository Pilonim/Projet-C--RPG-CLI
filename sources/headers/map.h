//
// Created by jonat on 16/10/2021.
//

#ifndef PROJET_C___JEU_2D_MAP_H
#define PROJET_C___JEU_2D_MAP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
void shuffle(int *array, int n);
int **initMap(Game **game, int stage);
int **mapGen(Game **game, int stage, int *npc, int npcSize);
void printMap(Game *game);
#endif //PROJET_C___JEU_2D_MAP_H
