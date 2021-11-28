//
// Created by ferre on 21/10/2021.
//

#ifndef MALLOCWORLD_PNJ_H
#define MALLOCWORLD_PNJ_H

#include "struct.h"

void initPNJ(PNJ* pnj);
void addToChest(PNJ* pnj, Player* player, int index);
void removeFromChest(PNJ* pnj, Player* player, int index, Item* items);
void repairPlayerItems(Player* player);
void showChest(PNJ *pnj);

#endif //MALLOCWORLD_PNJ_H
