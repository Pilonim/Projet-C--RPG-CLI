//
// Created by jonat on 23/10/2021.
//

#ifndef PROJET_C___JEU_2D_FIGHT_H
#define PROJET_C___JEU_2D_FIGHT_H
#include "struct.h"
#include "character.h"

void initStuff(int *nbWeapons,int *nbChest, int *nbPotions, int **weapons, int **potions, int **chest, Player *p, int *count);
int fight(Player *p, Mob *mob, int mobId, int nbMobs);
#endif //PROJET_C___JEU_2D_FIGHT_H
