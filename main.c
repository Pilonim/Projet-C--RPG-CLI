#include <stdio.h>

#define ARME 1
#define OUTIL 2
#define CRAFT 3
#define SOIN 4

typedef struct Item{
    int value;
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
} Player;

Item addInv(int value){
    //TODO
}

Player initPlayer(Player* player){
    player->hp = 100;
    player->hpMax = 100;
    player->exp = 0;
    player->lvl = 1;

    player->inventory[0] = addInv(1);
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
