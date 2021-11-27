//
// Created by kerel on 21/10/2021.
//

#include "craft.h"
#include "character.h"

Craft createCraft(int id,char* name,int materOne,int nbMaterOne,int materTwo,int nbMaterTwo,int lvlMin,int itemId){
    Craft* craft = malloc(sizeof(Craft));
    craft->id = id;
    craft->name = malloc(strlen(name));
    strcpy(craft->name,name);
    craft->materOne = materOne;
    craft->nbMaterOne = nbMaterOne;
    craft->materTwo = materTwo;
    craft->nbMaterTwo = nbMaterTwo;
    craft->lvlMin = lvlMin;
    craft->itemId = itemId;

    return *craft;
}

Craft* declareCraft(int* nbCraft){
    FILE* f = fopen("craft.txt","r+");
    if (f){
        int count = 0;
        char buffer[255];
        int id;
        char name[255];
        int materOne;
        int nbMaterOne;
        int materTwo;
        int nbMaterTwo;
        int lvlMin;
        int itemId;

        while (fgets(buffer,sizeof(buffer), f)){
            count += 1;
        }
        Craft* crafts = malloc(sizeof(Craft) * count);
        rewind(f);

        for (int i = 0; i < count ; i++) {
            fgets(buffer, sizeof(buffer), f);
            sscanf(buffer,"id: %d, name: %[^,], materOne: %d, nbMaterOne: %d, materTwo: %d, nbMaterTwo: %d, lvlMin: %d, itemId: %d",&(id),name,&(materOne),&(nbMaterOne),&(materTwo),&(nbMaterTwo),&(lvlMin),&(itemId));
            crafts[i] = createCraft(id,name,materOne,nbMaterOne,materTwo,nbMaterTwo,lvlMin,itemId);
        }
        fclose(f);
        *nbCraft = count;
        return crafts;

    } else{
        printf("No such file");
        return NULL;
    }
}

void isCraftable(Player* player, Craft* crafts, int nbCraft,Item* items, int* actualMap, Game *game){
    int materOne;
    int materTwo;
    int count = 0;
    int i;
    for(i=0;i<nbCraft;i++){
        game->isCraftable[i] = 0;
    }
    printf("Craft disponibles : \n");
    for (int j = 0; j < nbCraft; ++j) {
        materOne = 0;
        materTwo = 0;
        for (int i = 0; i < 10; ++i) {
            if(player->inventory[i].id == crafts[j].materOne && !materOne){ //check de la zone
                if(player->inventory[i].amount >= crafts[j].nbMaterOne){
                    materOne = 1;
                }
            }

            if(player->inventory[i].id == crafts[j].materTwo && crafts[j].materTwo != 0 && !materTwo){ //check de la zone
                if(player->inventory[i].amount >= crafts[j].nbMaterTwo){
                    materTwo = 1;
                }
            } else if(crafts[j].materTwo == 0){
                materTwo = 1;
            }


        }
        if(materOne && materTwo){
            count += 1;
            printf("%d : %s\n", crafts[j].id,crafts[j].name);
            game->isCraftable[j]= 1;
        }
    }
    if(count == 0){
        printf("Aucun\n");
    }
}

void craft(Player* player, Craft* crafts, int idCraft,Item* items, Game *game){
    int i;
    if(game->isCraftable[idCraft-1] == 0){
        printf("Vous ne pouvez pas craft cet item\n");
        return;
    }
    for (i = 0; i < 10; ++i) {
        if(player->inventory[i].id == crafts[idCraft-1].materOne){
            removeItem(player, i,crafts[idCraft-1].nbMaterOne);
        }

        if(player->inventory[i].id == crafts[idCraft-1].materTwo){
            removeItem(player, i,crafts[idCraft-1].nbMaterTwo);
        }
    }
    addInv(crafts->itemId,player,items);
}