#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARME 1
#define OUTIL 2
#define CRAFT 3
#define SOIN 4

typedef struct Item{
    int id;
    char name[255];
    int type; //arme, outil, ressource de craft ou soin
    int durability;
    int damage;
    int amount;
} Item;

typedef struct Player{
    int hp;
    int hpMax;
    int exp;
    int lvl;
    Item inventory[10];
    int nbItem;
} Player;

Item createItem(int id, char* name, int type, int durability, int damage){
    Item* newItem = malloc(sizeof(Item));
    newItem->id = id;
    strcpy(newItem->name,name);
    newItem->type = type;
    newItem->durability = durability;
    newItem->damage = damage;
    newItem->amount = 1;

    return *newItem;
}



void addInv(int id,Player* player){
    int i = 0;
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
            player->inventory[i] = createItem(1,"épée en bois", ARME, 10, 1);
            break;
        case 2 :
            player->inventory[i] = createItem(2,"Picohe en bois", OUTIL, 10, 0);
            break;
        case 3 :
            player->inventory[i] = createItem(3,"Serpe en bois", OUTIL, 10, 0);
            break;
        case 4 :
            player->inventory[i] = createItem(4,"Hache en bois", OUTIL, 10, 0);
            break;
        case 5 :
            player->inventory[i] = createItem(5,"Sapin", CRAFT, 0, 0);
            break;
        case 6 :
            player->inventory[i] = createItem(6,"Pierre", CRAFT, 0, 0);
            break;
        case 7 :
            player->inventory[i] = createItem(7,"Herbe", CRAFT, 0, 0);
            break;
        case 8 :
            player->inventory[i] = createItem(8,"Épée en pierre", ARME, 10, 2);
            break;
        case 9 :
            player->inventory[i] = createItem(9,"Lance en pierre", ARME, 8, 3);
            break;
        case 10 :
            break;
        case 11 :
            break;
        case 12 :
            break;
        case 13 :
            break;
        case 14 :
            break;
        case 15 :
            break;
        case 16 :
            break;
        case 17 :
            break;
        case 18 :
            break;
        case 19 :
            break;
        case 20 :
            break;
        case 21 :
            break;
        case 22 :
            break;
        case 23 :
            break;
        case 24 :
            break;
        case 25 :
            break;
        case 26 :
            break;
        case 27 :
            break;
        case 28 :
            break;
        case 29 :
            break;
        case 30 :
            break;
        case 31 :
            break;
        case 32 :
            break;
        case 33 :
            break;
        case 34 :
            break;
        default:
            printf("not an item");
            break;
    }
    player->nbItem  +=1;

}

Player initPlayer(Player* player){
    player->hp = 100;
    player->hpMax = 100;
    player->exp = 0;
    player->lvl = 1;
    player->nbItem = 0;
    Item item = createItem(0,"",0,0,0);

    for (int i = 0; i < 10; ++i) {
        player->inventory[i] = item;
    }

    addInv(1, player);
    addInv(2, player);
    addInv(3, player);
    addInv(4, player);
}

int main() {

    Player* player = malloc(sizeof(Player));
    initPlayer(player);

    printf("%d",player->inventory[1].id);

    return 0;
}
