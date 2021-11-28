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
#include "pnj.h"
#include "craft.h"
void move(Game *game, char dir);
void checkCase(Game *game, int vertical, int horizontal);
#endif //PROJET_C___JEU_2D_MOVE_H
