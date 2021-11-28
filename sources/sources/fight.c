//
// Created by jonat on 23/10/2021.
//

#include "../headers/fight.h"
void initStuff(int *nbWeapons,int *nbChest, int *nbPotions, int **weapons, int **potions, int **chest, Player *p, int *count){
    int i;
    for(i=0;i<10;i++){
        if(p->inventory[i].type == ARME && p->inventory[i].durability > 0){
            (*nbWeapons)+=1;
        }else if(p->inventory[i].type == ARMURE){
            (*nbChest)+=1;
        }else if(p->inventory[i].type == SOIN){
            (*nbPotions)+=1;
        }
    }
    if(*nbWeapons != 0){
        *weapons = malloc(sizeof(int) * *nbWeapons);
    }
    if(*nbChest != 0){
        *chest = malloc(sizeof(int) * *nbChest);
    }
    if(*nbPotions != 0){
        *potions = malloc(sizeof(int)* *nbPotions);
    }
    for(i=0;i<10;i++){
        if(p->inventory[i].type == ARME && p->inventory[i].durability > 0){
            (*weapons)[count[0]] = i;
            count[0]+=1;
        }else if(p->inventory[i].type == ARMURE){
            (*chest)[count[1]] = i;
            count[1]+=1;
        }else if(p->inventory[i].type == SOIN){
            (*potions)[count[2]] = i;
            count[2] += 1;
        }
    }
}

void firstStuff(int *nbWeapons, int *nbChest, int *weapons, int *chest, int *chosenWeapon, int *chosenChest, Player *p){
    int i;
    int choice;
    if(*nbWeapons == 1){
        *chosenWeapon = weapons[0];
    }else if(*nbWeapons != 0){
        printf("Vos armes : \n");
        for(i=0;i<*nbWeapons;i++){
            printf("[%d] nom : %s // degats : %0.1lf // durabilite : %0.1lf\n",i,p->inventory[weapons[i]].name,p->inventory[weapons[i]].effect,p->inventory[weapons[i]].durability);
        }
        printf("\nQuelle arme choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice >= *nbWeapons);
        *chosenWeapon = weapons[choice];
    }else{
        printf("VOUS N'AVEZ PAS D'ARME FUYEZ\n");
    }
    if(*nbChest == 1){
        *chosenChest = chest[0];
    }else if(*nbChest != 0){
        printf("Vos plastrons : \n");
        for(i=0;i<*nbChest;i++){
            printf("[%d] nom : %s // resistance : %0.1lf\n",i,p->inventory[chest[i]].name,p->inventory[chest[i]].effect);
        }
        printf("\nQuelle armure choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice >= *nbChest);
        *chosenChest = chest[choice];
    }
}

void startFight(Mob *mob, int nbMobs, int mobId, Mob * currentMob, double * mobHp, int *nbWeapons, Player *p, int *chosenWeapon, int *nbChest, double *armor, int * chosenChest){
    int i;
    for(i=0;i<nbMobs;i++){
        if(mob[i].id == mobId){
            *mobHp = mob[i].hp;
            *currentMob = mob[i];
            printf("VOUS ENTREZ EN COMBAT CONTRE : %s il a %0.2lf hp,", mob[i].name,mob[i].hp);
            if(*nbWeapons == 0){
                printf(" sans arme");
            }else{
                printf(" avec %s",p->inventory[*chosenWeapon].name);
            }
            if(*nbChest == 0){
                printf(" et sans armure avec %0.2lf hp\n",p->hp);
            }else{
                *armor = p->inventory[*chosenChest].effect;
                printf(" et avec %s avec %0.2lf hp\n", p->inventory[*chosenChest].name,p->hp);
            }
        }
    }
}

void attack(Player *p, int *chosenWeapon, double *mobHp, int *nbWeapons, int *count, int *weapons, int **newWeapons, int *check){
    int i;
    int choice;
    if(p->inventory[*chosenWeapon].durability > 0) {
        *mobHp -= p->inventory[*chosenWeapon].effect;
        *mobHp = *mobHp < 0 ? 0 : *mobHp;
        printf("Vous infligez %0.1lf domages au monstre, il lui reste : %0.1lf points de vie\n",p->inventory[*chosenWeapon].effect, *mobHp);
        p->inventory[*chosenWeapon].durability -= 1;
    }else{
        printf("Votre arme est cassee !");
        if(*nbWeapons > 1){
            count[0] = 0;
            for (i = 0; i < *nbWeapons; i++) {
                if (p->inventory[weapons[i]].durability > 0) {
                    count[0] += 1;
                }
            }
            if(count[0] > 0){
                printf(" Vous devez en choisir une autre : \n");
                printf("Vos armes : \n");
                *newWeapons = malloc(sizeof(int) * count[0]);
                count[0] = 0;
                for (i = 0; i < *nbWeapons; i++) {
                    if (p->inventory[weapons[i]].durability > 0) {
                        printf("[%d] nom : %s // degats : %0.1lf // durabilite : %0.1lf\n", count[0],
                               p->inventory[weapons[i]].name, p->inventory[weapons[i]].effect,
                               p->inventory[weapons[i]].durability);
                        (*newWeapons)[count[0]] = weapons[i];
                        count[0] += 1;
                    }
                }
                printf("\nQuelle arme choisissez-vous ?\n");
                do {
                    scanf("%d", &choice);
                } while (choice < 0 || choice >= count[0]);
                *chosenWeapon = (*newWeapons)[choice];
            } else {
                printf(" Vous devez fuir !\n");
                *check = 1;
                return;
            }
        }else{
            printf(" Vous devez fuir ! \n");
            *check = 1;
        }
    }
}

void takePotion(int *nbPotions, Player *p, int *potions, int *check){
    int i;
    int choice;
    if((*nbPotions) > 0){
        printf("Vos potions : \n");
        printf("[0] pour annule\n");
        for(i=0;i<*nbPotions;i++){
            printf("[%d] nom : %s // pv soigne : %0.1lf \n",i+1,p->inventory[potions[i]].name,p->inventory[potions[i]].effect,p->inventory[potions[i]].durability);
        }
        printf("\nQuelle potion choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice > *nbPotions);
        if(choice == 0){
            *check = 1;
            return;
        }else {
            if (p->hp + p->inventory[potions[choice - 1]].effect >= p->hpMax) {
                p->hp = p->hpMax;
            } else {
                p->hp += p->inventory[potions[choice - 1]].effect;
            }
            removeItem(p,potions[choice - 1],1);
        }
        *nbPotions-=1;
        if(*nbPotions == 0){
            printf("Attention, c'etait votre derniere\n");
        }else{
            printf("Il vous reste %d potions\n", *nbPotions);
        }
    }else{
        *check = 1;
        printf("Vous n'avez pas de potion ! \n");
    }
}

int runAway(int *check){
    int leave;
    int dice;
    printf("Vous voulez fuir ? En etes vous sur ?\n    1- Oui\n    2- Non\n");
    scanf("%d", &leave);
    switch (leave) {
        case 1:
            dice = 1+(rand()%10);
            printf("Vous lancez un d10 pour essayer de fuir, froussard\n");
            sleep(2);
            if(dice > 3){
                printf("%d, c'est un echec cuisant\n",dice);
            }else{
                printf("%d, Bravo !\n",dice);
                sleep(2);
                return 1;
            }
            break;
        case 2:
            *check = 1;
            break;
        default:
            printf("Ce n'est pas une reponse valide\n");
            break;
    }
    return 0;
}

int checkHps(double *mobHp, Mob *currentMob, double *armor, Player *p, Game *game){
    double mobDamages;
    if(*mobHp <= 0){
        if(*(game->currentMap) == 0 && game->player->lvl > 3 ){
            printf("Felicitation ! Vous avez gagne %d xp (Entrer pour terminer le combat)\n",0);
        }else if(*(game->currentMap) == 1 && game->player->lvl > 7){
            printf("Felicitation ! Vous avez gagne %d xp (Entrer pour terminer le combat)\n",0);
        }else {
            printf("Felicitation ! Vous avez gagne %d xp (Entrer pour terminer le combat)\n", (*currentMob).xp);
        }
        fflush(stdin);
        scanf("%*c");
        return (*currentMob).xp;
    }
    mobDamages = currentMob->damages-(currentMob->damages* *armor);
    p->hp -= mobDamages;
    p->hp = p->hp<0?0:p->hp;
    printf("%s vous attaque en retour pour %0.1lf point de degats, il vous reste : %0.1lf hp\n",(*currentMob).name,mobDamages,p->hp);
    if(p->hp == 0){
        printf("Vous etes morts lamentablement (Entrer pour quitter la partie)\n");
        fflush(stdin);
        scanf("%*c");
        return -1;
    }
    return 0;
}

int fight(Player *p, Mob *mob, int mobId, int nbMobs, Game *game){
    int *nbWeapons = malloc(sizeof(int));
    *nbWeapons = 0;
    int *weapons;
    int *nbChest = malloc(sizeof(int));
    *nbChest = 0;
    int *newWeapons;
    int *nbPotions = malloc(sizeof(int));
    *nbPotions = 0;
    int *count = malloc(sizeof(int)*3);
    count[0] = 0;
    count[1] = 0;
    count[2] = 0;
    int xp;
    int *chest;
    int *potions;
    int *check = malloc(sizeof(int));
    *check = 0;
    double *armor = malloc(sizeof(double));
    *armor = 0;
    Mob *currentMob = malloc(sizeof(Mob));
    double *mobHp = malloc(sizeof(double));
    int *chosenWeapon = malloc(sizeof(int));
    int *chosenChest = malloc(sizeof(int));
    int choice;
    srand(time(NULL));
    initStuff(nbWeapons,nbChest,nbPotions,&weapons,&potions,&chest,p,count);
    firstStuff(nbWeapons,nbChest,weapons,chest,chosenWeapon,chosenChest,p);
    startFight(mob,nbMobs,mobId,currentMob,mobHp,nbWeapons,p,chosenWeapon,nbChest,armor,chosenChest);
    while(1){
        printf("Que voulez vous faire ?\n   -Attaquer (tapez 1)\n   -Boire une potion (tapez 2)\n   -Fuir (tapez 3)\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                attack(p,chosenWeapon,mobHp,nbWeapons,count,weapons,&newWeapons,check);
                break;
            case 2:
                takePotion(nbPotions,p,potions,check);
                break;
            case 3:
                if(runAway(check)){
                    return 0;
                }else {
                    break;
                }
        }
        if(*check){
            *check = 0;
            continue;
        }
        xp = checkHps(mobHp,currentMob,armor,p,game);
        if(xp){
            return xp;
        }
    }
}