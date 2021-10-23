//
// Created by jonat on 23/10/2021.
//

#include "fight.h"

int fight(Player *p, Mob *mob, int mobId, int nbMobs){
    int nbWeapons = 0;
    int *weapons;
    int nbChest = 0;
    int nbPotions = 0;
    int count[2] = {0,0};
    int *chest;
    int check = 0;
    int dice;
    double armor = 0;
    int leave;
    Mob currentMob;
    double mobDamages;
    double mobHp;
    Item chosenWeapon;
    Item choseChest;
    int choice;
    srand(time(NULL));
    int i=0;
    for(i=0;i<10;i++){
        if(p->inventory[i].type == ARME){
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
    for(i=0;i<10;i++){
        if(p->inventory[i].type == ARME){
            weapons[count[0]] = i;
            count[0]+=1;
        }else if(p->inventory[i].type == ARMURE){
            chest[count[1]] = i;
            count[i]+=1;
        }
    }
    if(nbWeapons == 1){
        chosenWeapon = p->inventory[weapons[0]];
    }else if(nbWeapons != 0){
        printf("Vos armes : \n");
        for(i=0;i<nbWeapons;i++){
            printf("[%d] nom : %s // degats : %lf // durabilite : %lf\n",i,p->inventory[weapons[i]].name,p->inventory[weapons[i]].effect,p->inventory[weapons[i]].durability);
        }
        printf("\nQuelle arme choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice > nbWeapons);
        chosenWeapon = p->inventory[choice];
    }else{
        printf("VOUS N'AVEZ PAS D'ARME FUYEZ\n");
    }
    if(nbChest == 1){
        choseChest = p->inventory[chest[0]];
    }else if(nbChest != 0){
        printf("Vos plastrons : \n");
        for(i=0;i<nbChest;i++){
            printf("[%d] nom : %s // degats : %lf // durabilite : %lf\n",i,p->inventory[weapons[i]].name,p->inventory[weapons[i]].effect,p->inventory[weapons[i]].durability);
        }
        printf("\nQuelle armure choisissez-vous ?\n");
        do {
            scanf("%d",&choice);
        }while(choice < 0 || choice > nbChest);
        choseChest = p->inventory[choice];
    }
    for(i=0;i<nbMobs;i++){
        if(mob[i].id == mobId){
            mobHp = mob[i].hp;
            currentMob = mob[i];
            printf("VOUS ENTREZ EN COMBAT CONTRE : %s", mob[i].name);
            if(nbWeapons == 0){
                printf(" sans arme, fuyez");
            }else{
                printf(" avec %s",chosenWeapon.name);
            }
            if(nbChest == 0){
                printf(" et sans armure\n");
            }else{
                armor = choseChest.effect;
                printf(" et avec %s\n",choseChest.name);
            }
        }
    }
    while(1){
        printf("Que voulez vous faire ?\n   -Attaquer (tapez 1)\n   -Boire une potion (tapez 2)\n   -Fuir (tapez 3)\n");
        scanf("%d",&choice);
        switch (choice) {
            case 1:
                mobHp-=chosenWeapon.effect;
                printf("Vous infligez %0.1lf domages au monstre, il lui reste : %0.1lf points de vie\n",chosenWeapon.effect,mobHp);
                break;
            case 2:
                if(nbPotions > 0){
                    p->hp+=50;
                    nbPotions-=1;
                    if(nbPotions == 0){
                        printf("Attention, c'etait votre derniere\n");
                    }else{
                        printf("Il vous reste %d porions\n", nbPotions);
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