//
// Created by kerel on 21/10/2021.
//

#ifndef TESTOO_CRAFT_H
#define TESTOO_CRAFT_H

#include "struct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Craft createCraft(int id,char* name,int materOne,int nbMaterOne,int materTwo,int nbMaterTwo,int lvlMin,int itemId);
Craft* declaredCraft(int* nbCraft);
void isCraftable(Player* player, Craft* crafts, int nbCraft);
void craft(Player* player, Craft* crafts, int idCraft);

#endif //TESTOO_CRAFT_H
