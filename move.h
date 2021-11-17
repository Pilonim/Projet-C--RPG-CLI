//
// Created by jonat on 21/10/2021.
//

#ifndef PROJET_C___JEU_2D_MOVE_H
#define PROJET_C___JEU_2D_MOVE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "farm.h"
#include "fight.h"
void move(int ***map, int height, int width, int **startPosition, char dir, int *actualMap, Player *p, int **diedNpcs, int *nbDiedNpcs, Mob *mobs, int nbMobs, int *xpWin, int *onPortal, Item * items);
void checkCase(int ***map, int **position, int vertical, int horizontal, int *actualMap, Player *p, int **diedNpcs, int *nbDiedNpcs, Mob *mobs, int nbMobs, int *xpWin, int *onPortal, Item * items);
#endif //PROJET_C___JEU_2D_MOVE_H
