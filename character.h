//
// Created by kerel on 21/10/2021.
//

#ifndef MALLOC_WORLD_CHARACTER_H
#define MALLOC_WORLD_CHARACTER_H
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define ARME 1
#define OUTIL 2
#define CRAFT 3
#define SOIN 4
#define ARMURE 5

Item createItem(int id, char* name, int type, int durability,int maxDurability, double effect);
void addInv(int id,Player* player);
void removeItem(Player* player, int index);
Player initPlayer(Player* player);
void showInventory(Player *p);



#endif //MALLOC_WORLD_CHARACTER_H
