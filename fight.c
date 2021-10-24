//
// Created by jonat on 23/10/2021.
//

#include "fight.h"

int fight(Player *p, Mob *mob, int mobId, int nbMobs){
    int nbWeapons = 0;
    int *weapons;
    int nbChest = 0;
    int *newWeapons;
    int nbPotions = 0;
    int count[3] = {0,0,0};
    int *chest;
    int *potions;
    int check = 0;
    int dice;
    double armor = 0;
    int leave;
    Mob currentMob;
    double mobDamages;
    double mobHp;
    int chosenWeapon;
    int chosenChest;
    int choice;
    srand(time(NULL));
    int i=0;
    for(i=0;i<10;i++){
        if(p->inventory[i].type == ARME && p->inventory[i].durability > 0){
            nbWeapons+=1;
        }else if(p->inventory[i].type == ARMURE){
            nbChest+=1;
        }else if(p->inventory[i].type == SOIN){
            nbPotions+=1;
        }
    }
    if(nbWeapons != 0){
        weapons = malloc(sizeof(int) * nbWeapons);
    }
    if(nbChest != 0){
        chest = malloc(sizeof(int) * nbChest);
    }
    if(nbPotions != 0){
        potions = malloc(sizeof(int)*nbPotions);
    }
    for(i=0;i<10;i++){
        if(p->inventory[i].type == ARME && p->inventory[i].durability > 0){
            weapons[count[0]] = i;
            count[0]+=1;
        }else if(p->inventory[i].type == ARMURE){
            chest[count[1]] = i;
            count[1]+=1;
        }else if(p->inventory[i].type == SOIN){
            potions[count[2]] = i;
            count[2] += 1;
        }
    }
    if(nbWeapons == 1){
        chosenWeapon = weapons[0];
    }else if(nbWeapons != 0){
        printf("Vos armes : \n");
        for(i=0;i<nbWeapons;i++){
            printf("[%d] nom : %s // degats : %0.1lf // durabilite : %0.1lf\n",i,p->inventory[weapons[i]].name,p->inventory[weapons[i]].effect,p->inventory[weapons[i]].durability);
        }
        printf("\nQuelle arme choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice >= nbWeapons);
        chosenWeapon = weapons[choice];
    }else{
        printf("VOUS N'AVEZ PAS D'ARME FUYEZ\n");
    }
    if(nbChest == 1){
        chosenChest = chest[0];
    }else if(nbChest != 0){
        printf("Vos plastrons : \n");
        for(i=0;i<nbChest;i++){
            printf("[%d] nom : %s // resistance : %0.1lf\n",i,p->inventory[chest[i]].name,p->inventory[chest[i]].effect);
        }
        printf("\nQuelle armure choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice >= nbChest);
        chosenChest = chest[choice];
    }
    for(i=0;i<nbMobs;i++){
        if(mob[i].id == mobId){
            mobHp = mob[i].hp;
            currentMob = mob[i];
            printf("VOUS ENTREZ EN COMBAT CONTRE : %s", mob[i].name);
            if(nbWeapons == 0){
                printf(" sans arme, fuyez");
            }else{
                printf(" avec %s",p->inventory[chosenWeapon].name);
            }
            if(nbChest == 0){
                printf(" et sans armure\n");
            }else{
                armor = p->inventory[chosenChest].effect;
                printf(" et avec %s\n", p->inventory[chosenChest].name);
            }
        }
    }
    while(1){
        printf("Que voulez vous faire ?\n   -Attaquer (tapez 1)\n   -Boire une potion (tapez 2)\n   -Fuir (tapez 3)\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                if(p->inventory[chosenWeapon].durability > 0) {
                    mobHp -= p->inventory[chosenWeapon].effect;
                    mobHp = mobHp < 0 ? 0 : mobHp;
                    printf("Vous infligez %0.1lf domages au monstre, il lui reste : %0.1lf points de vie\n",p->inventory[chosenWeapon].effect, mobHp);
                    p->inventory[chosenWeapon].durability -= 1;
                }else{
                    printf("Votre arme est cassee !");
                    if(nbWeapons > 1){
                        count[0] = 0;
                        for (i = 0; i < nbWeapons; i++) {
                            if (p->inventory[weapons[i]].durability > 0) {
                                count[0] += 1;
                            }
                        }
                        if(count[0] > 0){
                        printf(" Vous devez en choisir une autre : \n");
                        printf("Vos armes : \n");
                        newWeapons = malloc(sizeof(int) * count[0]);
                        count[0] = 0;
                        for (i = 0; i < nbWeapons; i++) {
                            if (p->inventory[weapons[i]].durability > 0) {
                                printf("[%d] nom : %s // degats : %0.1lf // durabilite : %0.1lf\n", count[0],
                                       p->inventory[weapons[i]].name, p->inventory[weapons[i]].effect,
                                       p->inventory[weapons[i]].durability);
                                newWeapons[count[0]] = weapons[i];
                                count[0] += 1;
                            }
                        }
                            printf("\nQuelle arme choisissez-vous ?\n");
                            do {
                                scanf("%d", &choice);
                            } while (choice < 0 || choice >= count[0]);
                            chosenWeapon = newWeapons[choice];
                            printf("arme choisie : %s / chosenWeapon: %d\n", p->inventory[chosenWeapon].name,
                                   chosenWeapon);
                        } else {
                            printf(" Vous devez fuir !\n");
                            check = 1;
                            break;
                        }
                    }else{
                        printf(" Vous devez fuir ! \n");
                    }
                }
                break;
            case 2:
                if(nbPotions > 0){
                        printf("Vos potions : \n");
                        printf("[0] pour annule\n");
                        for(i=0;i<nbPotions;i++){
                            printf("[%d] nom : %s // pv soigne : %0.1lf \n",i+1,p->inventory[potions[i]].name,p->inventory[potions[i]].effect,p->inventory[potions[i]].durability);
                        }
                        printf("\nQuelle potion choisissez-vous ?\n");
                        do {
                            scanf("%d",&choice);
                        }while(choice < 0 || choice > nbPotions);
                        if(choice == 0){
                            check = 1;
                            break;
                        }else {
                            if (p->hp + p->inventory[potions[choice - 1]].effect >= p->hpMax) {
                                p->hp = p->hpMax;
                            } else {
                                p->hp += p->inventory[potions[choice - 1]].effect;
                            }
                            removeItem(p,potions[choice - 1]);
                        }
                    nbPotions-=1;
                    if(nbPotions == 0){
                        printf("Attention, c'etait votre derniere\n");
                    }else{
                        printf("Il vous reste %d potions\n", nbPotions);
                    }
                }else{
                    check = 1;
                    printf("Vous n'avez pas de potion ! \n");
                }
                break;
            case 3:
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
                            return 0;
                        }
                        break;
                    case 2:
                        check = 1;
                        break;
                    default:
                        printf("Ce n'est pas une reponse valide\n");
                        break;
                }
                break;
            default:
                break;

        }
        if(check){
            check = 0;
            continue;
        }
        if(mobHp <= 0){
            printf("Felicitation ! Vous avez gagne %d xp (Entrer pour terminer le combat)\n",currentMob.xp);
            fflush(stdin);
            scanf("%*c");
            return currentMob.xp;
        }
        mobDamages = currentMob.damages-(currentMob.damages*armor);
        p->hp -= mobDamages;
        p->hp = p->hp<0?0:p->hp;
        printf("%s vous attaque en retour pour %0.1lf point de degats, il vous reste : %0.1lf hp\n",currentMob.name,mobDamages,p->hp);
        if(p->hp == 0){
            printf("Vous etes morts lamentablement (Entrer pour quitter la partie)\n");
            fflush(stdin);
            scanf("%*c");
            return -1;
        }
    }

}