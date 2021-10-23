//
// Created by ferre on 21/10/2021.
//

#ifndef MALLOCWORLD_PNJ_H
#define MALLOCWORLD_PNJ_H

#include "struct.h"

void initPNJ(PNJ*);
void addToChest(PNJ*, Player*, int);
void removeFromChest(PNJ*, Player*, int);
int chestIsFull(PNJ*);
int getFirstEmptySlot(PNJ*);
void repairPlayerItems(Player*);
void showChest(PNJ *p);

#endif //MALLOCWORLD_PNJ_H
