//
// Created by jonat on 21/10/2021.
//

#ifndef PROJET_C___JEU_2D_MOVE_H
#define PROJET_C___JEU_2D_MOVE_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void move(int **map, int height, int width, int *startPosition, char dir);
void checkCase(int **map, int *position, int vertical, int horizontal);
#endif //PROJET_C___JEU_2D_MOVE_H
