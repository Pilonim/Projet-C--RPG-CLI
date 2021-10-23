//
// Created by kerel on 21/10/2021.
//

#ifndef MALLOC_WORLD_CHARACTER_H
#define MALLOC_WORLD_CHARACTER_H
#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



Item createItem(int id, char* name, int type, int durability,int maxDurability, double effect);
void addInv(int id,Player* player);
void removeItem(Player* player, int index);
void initPlayer(Player* player);
void showInventory(Player *p);



#endif //MALLOC_WORLD_CHARACTER_H
