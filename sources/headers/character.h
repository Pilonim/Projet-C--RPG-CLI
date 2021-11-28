//
// Created by kerel on 21/10/2021.
//

#ifndef MALLOC_WORLD_CHARACTER_H
#define MALLOC_WORLD_CHARACTER_H
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARME 1
#define OUTIL 2
#define CRAFT 3
#define SOIN 4
#define ARMURE 5

void showPlayer(Game *game);
void levelUp(Player *p);
Item* declareItem(int* nbItem);
Item createItem(int id, char* name, int type, double durability,double maxDurability, double effect);
void addInv(int id,Player* player,Item* items);
void removeItem(Player* player, int index,int nbItem);
void showInventory(Player *p);
Player *initPlayer(Item *items);



#endif //MALLOC_WORLD_CHARACTER_H
