//
// Created by jonat on 21/10/2021.
//

#ifndef PROJET_C___JEU_2D_MOBS_H
#define PROJET_C___JEU_2D_MOBS_H
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
typedef struct mob_s{
    int id;
    char *name;
    int damages;
    int xp;
    int hp;
}Mob;

Mob *declareMobs(int *nbMobs);
Mob createMob(int id, char *name, int damages, int xp, int hp);
#endif //PROJET_C___JEU_2D_MOBS_H
