//
// Created by ferre on 17/10/2021.
//

#include <stdlib.h>
#include "pnj.h"
#include "character.h"

void initPNJ(PNJ *pnj){
    pnj->chestSize = 0;
    pnj->chest = malloc(sizeof(Item));

}

void addToChest(PNJ *pnj, Player *player, int index){
    Item* temp = malloc(sizeof(Item) * (pnj->chestSize + 1)); // 1

    for(int k = 0; k < pnj->chestSize; k++){ // 0
        temp[k] = pnj->chest[k];
    }

    temp[pnj->chestSize] = player->inventory[index];
    removeItem(player, index, player->inventory[index].amount); // demander combien ?
    free(pnj->chest);
    pnj->chestSize = pnj->chestSize + 1; //1
    pnj->chest = malloc(sizeof(Item) * pnj->chestSize); // 1

    for(int i = 0; i < pnj->chestSize; i++){ // 0
        pnj->chest[i] = temp[i];
    }

}

void removeFromChest(PNJ *pnj, Player *player, int index, Item *items){

    if(pnj->chestSize == 0){
        return;
    }

    Item *temp;
    if(pnj->chestSize > 1) {
        temp = malloc(sizeof(Item) * pnj->chestSize - 1);
    }else{
        temp = malloc(sizeof(Item));
    }

    int cpt = 0;

    for(int k = 0; k < pnj->chestSize; k++){
        if(k == index){
            continue;
        }else{
            temp[cpt] = pnj->chest[k];
            cpt++;
        }
    }

    addInv(pnj->chest[index].id, player, items);

    free(pnj->chest);
    pnj->chestSize = pnj->chestSize - 1;
    pnj->chest = malloc(sizeof(Item) * pnj->chestSize);



    for (int i = 0; i < pnj->chestSize; ++i) {
        pnj->chest[i] = temp[i];
    }

    free(temp);
}

int chestIsFull(PNJ* pnj){
    int isFull = 0;
    for (int k = 0; k < pnj->chestSize; ++k) {
        if(pnj->chest[k].id == 0){
            isFull = 1;
            return isFull;
        }
    }

    return isFull;
}

int getFirstEmptySlot(PNJ *pnj){
    for (int k = 0; k < pnj->chestSize; ++k) {
        if(pnj->chest[k].id == 0){
            return k;
        }
    }

    return -1;
}

void repairPlayerItems(Player *player){
    for (int k = 0; k < 10; ++k) {
        if(player->inventory[k].id != 0){
            player->inventory[k].durability = player->inventory[k].maxDurability;
        }
    }
}

void showChest(PNJ *p){
    int i;
    for(i=0;i<10;i++){
        if(p->chest[i].id != 0){
            if(p->chest[i].type == CRAFT){
                printf("index : %d // nom : %s // quantite : %d\n",i,p->chest[i].name,p->chest[i].amount);
            }else if(p->chest[i].type == OUTIL){
                printf("index : %d // nom : %s // durabilite : %0.1lf\n",i,p->chest[i].name,p->chest[i].durability);
            }else if(p->chest[i].type == ARME){
                printf("index : %d // nom : %s // degats : %0.1lf // durabilite : %0.1lf\n",i,p->chest[i].name,p->chest[i].effect,p->chest[i].durability);
            }else if(p->chest[i].type == ARMURE){
                printf("index : %d // nom : %s // armure : %lf\n",i,p->chest[i].name,p->chest[i].effect);
            }else if(p->chest[i].type == SOIN) {
                printf("index : %d // nom : %s // soin : %lf hp\n",i,p->chest[i].name,p->chest[i].effect);
            }
        }
    }
}