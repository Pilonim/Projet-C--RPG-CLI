//
// Created by jonat on 21/10/2021.
//

#include "mobs.h"

Mob createMob(int id, char *name, int damages, int xp, double hp, int stage){
    Mob *mob = malloc(sizeof(Mob));
    mob->id = id;
    mob->name = malloc(strlen(name));
    strcpy(mob->name,name);
    mob->damages = damages;
    mob->xp = xp;
    mob->hp = hp;
    mob->stage = stage;
    return *mob;
}

Mob *declareMobs(int *nbMobs){
    FILE *f = fopen("../mobs.txt","r+");
    if(f) {
        int count = 0;
        int i;
        char buffer[255];
        int id;
        int xp;
        double hp;
        int damages;
        int stage;
        char name[255];
        while (fgets(buffer, sizeof(buffer), f)) {
            count+=1;
        }
        Mob *mobs = malloc(sizeof(Mob) * count);
        rewind(f);
        for(i=0;i<count;i++){
            fgets(buffer, sizeof(buffer), f);
            //printf("%s",buffer);
            sscanf(buffer,"name: %[^,], id: %d, damages: %d, hp: %lf, xp: %d, stage: %d",name,&(id),&(damages),&(hp),&(xp),&(stage));
            //printf("%d",stage);
            mobs[i] = createMob(id,name,damages,xp,hp,stage);
        }
        fclose(f);
        *nbMobs = count;
        printf("\n");
        return mobs;
    }else{
        printf("wtf bro");
        return NULL;
    }

}

void printMobs(Mob *mobs, int nbMobs){
    int i;
    for(i=0;i<nbMobs;i++){
        printf("nom : %s, id : %d, damages : %d, hp : %lf, xp : %d, stage : %d\n",mobs[i].name,mobs[i].id,mobs[i].damages,mobs[i].hp,mobs[i].xp,mobs[i].stage);
    }
}