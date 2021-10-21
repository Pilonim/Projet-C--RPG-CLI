//
// Created by jonat on 21/10/2021.
//

#include "mobs.h"

Mob createMob(int id, char *name, int damages, int xp, int hp){
    Mob *mob = malloc(sizeof(Mob));
    mob->id = id;
    mob->name = malloc(strlen(name));
    strcpy(mob->name,name);
    mob->damages = damages;
    mob->xp = xp;
    mob->hp = hp;
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
        int hp;
        int damages;
        char name[255];
        while (fgets(buffer, sizeof(buffer), f)) {
            count+=1;
        }
        Mob *mobs = malloc(sizeof(Mob) * count);
        rewind(f);
        for(i=0;i<count;i++){
            fgets(buffer, sizeof(buffer), f);
//            printf("%s",buffer);
            sscanf(buffer,"name: %[^,], id: %d, damages: %d, hp: %d, xp: %d",name,&(id),&(damages),&(hp),&(xp));
            mobs[i] = createMob(id,name,damages,hp,xp);
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