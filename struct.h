//
// Created by kerel on 16/10/2021.
//

#ifndef MALLOC_WORLD_STRUCT_H
#define MALLOC_WORLD_STRUCT_H
typedef struct Item{
    int id;
    char name[255];
    int type; //arme, outil, ressource de craft ou soin
    double durability;
    double maxDurability;
    double effect;
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
//salut les bg.
#endif //MALLOC_WORLD_STRUCT_H

