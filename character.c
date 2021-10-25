//
// Created by kerel on 21/10/2021.
//

#include "character.h"


Item createItem(int id, char* name, int type, int durability,int maxDurability, double effect){
    Item* newItem = malloc(sizeof(Item));
    newItem->id = id;
    strcpy(newItem->name,name);
    newItem->type = type;
    newItem->durability = durability;
    newItem->maxDurability = maxDurability;
    newItem->effect = effect;
    newItem->amount = 1;

    return *newItem;
}

void addInv(int id,Player* player){
    int i = 0;

    for (int j = 0; j < 10; ++j) {
        if(player->inventory[j].id == id){
            if(player->inventory[j].amount < 20 && player->inventory[j].type == CRAFT){
                player->inventory[j].amount +=1;
                return;
            }
        }
    }

    if(player->nbItem == 10){
        printf("Votre inventaire est plein");
        return;
    }
    for (i ; i < 10; ++i) {
        if(player->inventory[i].id == 0)
            break;
    }

    switch (id) {
        case 1 :
            player->inventory[i] = createItem(1,"épée en bois", ARME, 10,10, 1);
            break;
        case 2 :
            player->inventory[i] = createItem(2,"Pioche en bois", OUTIL, 10,10, 0);
            break;
        case 3 :
            player->inventory[i] = createItem(3,"Serpe en bois", OUTIL, 10,10, 0);
            break;
        case 4 :
            player->inventory[i] = createItem(4,"Hache en bois", OUTIL, 10,10, 0);
            break;
        case 5 :
            player->inventory[i] = createItem(5,"Sapin", CRAFT, 0,0, 0);
            break;
        case 6 :
            player->inventory[i] = createItem(6,"Pierre", CRAFT, 0,0, 0);
            break;
        case 7 :
            player->inventory[i] = createItem(7,"Herbe", CRAFT, 0,0, 0);
            break;
        case 8 :
            player->inventory[i] = createItem(8,"Épée en pierre", ARME, 10,10, 2);
            break;
        case 9 :
            player->inventory[i] = createItem(9,"Lance en pierre", ARME, 8,8, 3);
            break;
        case 10 :
            player->inventory[i] = createItem(10,"Marteau en pierre", ARME, 5,5, 4);
            break;
        case 11 :
            player->inventory[i] = createItem(11,"Plastron en pierre", ARMURE, 0,0, 0.1);
            break;
        case 12 :
            player->inventory[i] = createItem(12,"Pioche en pierre", OUTIL, 10,10, 0);
            break;
        case 13 :
            player->inventory[i] = createItem(13,"Serpe en pierre", OUTIL, 10,10, 0);
            break;
        case 14 :
            player->inventory[i] = createItem(14,"Hache en pierre", OUTIL, 10,10, 0);
            break;
        case 15 :
            player->inventory[i] = createItem(15,"Potion de vie I", SOIN, 0,0, 30);
            break;
        case 16 :
            player->inventory[i] = createItem(16,"Hêtre", CRAFT, 0,0, 0);
            break;
        case 17 :
            player->inventory[i] = createItem(17,"Fer", CRAFT, 0,0, 0);
            break;
        case 18 :
            player->inventory[i] = createItem(18,"Lavande", CRAFT, 0,0, 0);
            break;
        case 19 :
            player->inventory[i] = createItem(19,"Épée en fer", ARME, 10,10, 5);
            break;
        case 20 :
            player->inventory[i] = createItem(20,"Lance en fer", ARME, 8,8, 7);
            break;
        case 21 :
            player->inventory[i] = createItem(21,"Marteau en fer", ARME, 5,5, 10);
            break;
        case 22 :
            player->inventory[i] = createItem(22,"Plastron en fer", ARMURE, 0,0, 0.2);
            break;
        case 23 :
            player->inventory[i] = createItem(23,"Pioche en fer", OUTIL, 10,10, 0);
            break;
        case 24 :
            player->inventory[i] = createItem(24,"Serpe en fer", OUTIL, 10,10, 0);
            break;
        case 25 :
            player->inventory[i] = createItem(25,"Hache en fer", OUTIL, 10,10, 0);
            break;
        case 26 :
            player->inventory[i] = createItem(26,"Potion de vie II", SOIN, 0,0, 80);
            break;
        case 27 :
            player->inventory[i] = createItem(27,"Chene", CRAFT, 0,0, 0);
            break;
        case 28 :
            player->inventory[i] = createItem(28,"Diamant", CRAFT, 0,0, 0);
            break;
        case 29 :
            player->inventory[i] = createItem(29,"Chanvre", CRAFT, 0,0, 0);
            break;
        case 30 :
            player->inventory[i] = createItem(30,"Épée en diamant", ARME, 10,10, 10);
            break;
        case 31 :
            player->inventory[i] = createItem(31,"Lance en diamant", ARME, 8,8, 15);
            break;
        case 32 :
            player->inventory[i] = createItem(32,"Marteau en diamant", ARME, 5,5, 20);
            break;
        case 33 :
            player->inventory[i] = createItem(33,"Plastron en diamant", ARMURE, 0,0, 0.4);
            break;
        case 34 :
            player->inventory[i] = createItem(34,"Potion de vie III", SOIN, 1,0, 200);
            break;
        default:
            printf("not an item");
            break;
    }

    player->nbItem  +=1;

}

void removeItem(Player* player, int index){
    int choice = 0;
    if(player->inventory[index].amount == 1){
        player->inventory[index] = createItem(0, "", 0, 0, 0, 0);
        player->nbItem -= 1;
    } else {
        printf("Combien d\'item voulez-vous supprimmer : \n");
        scanf("%d",&choice);
        player->inventory[index].amount -= choice;

        if (player->inventory[index].amount <= 0){
            player->inventory[index] = createItem(0, "", 0, 0, 0, 0);
            player->nbItem -= 1;
        }
    }
}

void showPlayer(Player* player){
    printf("hp : %d / %d\n", player->hp,player->hpMax);
    printf("exp : %d / %d", player->exp,player->expMax);
    printf("lvl : %d", player->lvl);
}


Player initPlayer(Player* player){
    player->hp = 100;
    player->hpMax = 100;
    player->exp = 0;
    player->lvl = 1;
    player->nbItem = 0;
    Item item = createItem(0,"",0,0,0,0);

    for (int i = 0; i < 10; ++i) {
        player->inventory[i] = item;
    }

    addInv(1, player);
    addInv(2, player);
    addInv(3, player);
    addInv(4, player);
}