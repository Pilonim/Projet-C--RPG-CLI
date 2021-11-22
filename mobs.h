//
// Created by jonat on 21/10/2021.
//

#ifndef PROJET_C___JEU_2D_MOBS_H
#define PROJET_C___JEU_2D_MOBS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "struct.h"

Mob *declareMobs(int *nbMobs);
Mob createMob(int id, char *name, int damages, int xp, double hp, int stage);
void printMobs(Mob *mobs, int nbMobs);
void respawn(Game *game);
#endif //PROJET_C___JEU_2D_MOBS_H
