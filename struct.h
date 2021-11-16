//
// Created by kerel on 16/10/2021.
//

#ifndef MALLOC_WORLD_STRUCT_H
#define MALLOC_WORLD_STRUCT_H
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define ARME 1
#define OUTIL 2
#define CRAFT 3
#define SOIN 4
#define ARMURE 5

typedef struct Item{
    int id;
    char name[255];
    int type; //arme, outil, ressource de craft ou soin
    double durability;
    double maxDurability;
    double effect;
    int amount;
} Item;

typedef struct Craft{
    int id;
    char* name;
    int materOne;
    int nbMaterOne;
    int materTwo;
    int nbMaterTwo;
    int lvlMin;
    int itemId;
} Craft;

typedef struct Player{
    double hp;
    double hpMax;
    int exp;
    int expMax;
    int lvl;
    Item inventory[10];
    int nbItem;
} Player;

typedef struct PNJ{
    int chestSize;
    Item* chest;

}PNJ;

typedef struct mob_s{
    int id;
    char *name;
    int damages;
    int xp;
    double hp;
    int stage;
}Mob;
#endif //MALLOC_WORLD_STRUCT_H

