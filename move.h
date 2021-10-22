//
// Created by jonat on 21/10/2021.
//

#ifndef PROJET_C___JEU_2D_MOVE_H
#define PROJET_C___JEU_2D_MOVE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "farm.h"
void move(int ***map, int height, int width, int **startPosition, char dir, int *actualMap, Player *p);
void checkCase(int ***map, int **position, int vertical, int horizontal, int *actualMap, Player *p);
#endif //PROJET_C___JEU_2D_MOVE_H
