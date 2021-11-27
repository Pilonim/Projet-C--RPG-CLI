//
// Created by kerel on 21/10/2021.
//

#include "character.h"


Item createItem(int id, char* name, int type, double durability,double maxDurability, double effect){
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

Item* declareItem(int* nbItem){
    FILE* f = fopen("items.txt","r+");

    if (f) {
        int count = 0;
        char buffer[255];
        int id;
        char name[255];
        int type;
        double durability;
        double maxDurability;
        double effect;

        while (fgets(buffer, sizeof(buffer), f)) {
            count += 1;
        }
        Item *items = malloc(sizeof(Item) * count);
        rewind(f);

        for (int i = 0; i < count; i++) {
            fgets(buffer, sizeof(buffer), f);
            sscanf(buffer, "id: %d, name: %[^,], type: %d, durability: %lf, maxDurability: %lf, effect: %lf", &(id),
                   name, &(type), &(durability), &(maxDurability), &(effect));
            items[i] = createItem(id, name, type, durability, maxDurability, effect);
        }
        fclose(f);
        *nbItem = count;
        return items;
    } else {
        printf("No such file");
        return NULL;
    }
}

void addInv(int id,Player* player,Item* items){
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

    for (; i < 10; ++i) {
        if(player->inventory[i].id == 0)
            break;
    }

    id-=1;
    //printf("%d %s %d %lf %lf %lf\n",items[id].id,items[id].name,items[id].type,items[id].durability,items[id].maxDurability,items[id].effect);
    player->inventory[i] = createItem(items[id].id,items[id].name,items[id].type,items[id].durability,items[id].maxDurability,items[id].effect);
    /*
    switch (id) {
        case 1 :
            player->inventory[i] = createItem(1,"Epee en bois", ARME, 10,10, 1);
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
            player->inventory[i] = createItem(8,"Epee en pierre", ARME, 10,10, 2);
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
            player->inventory[i] = createItem(16,"Hetre", CRAFT, 0,0, 0);
            break;
        case 17 :
            player->inventory[i] = createItem(17,"Fer", CRAFT, 0,0, 0);
            break;
        case 18 :
            player->inventory[i] = createItem(18,"Lavande", CRAFT, 0,0, 0);
            break;
        case 19 :
            player->inventory[i] = createItem(19,"Epee en fer", ARME, 10,10, 5);
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
            player->inventory[i] = createItem(30,"Epee en diamant", ARME, 10,10, 10);
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
*/
    player->nbItem  +=1;

}

void removeItem(Player* player, int index, int nbItem){
    int choice = 0;
            player->nbItem -= 1;
    if(player->inventory[index].amount <= 1){
        player->inventory[index] = createItem(0, "", 0, 0, 0, 0);
        player->nbItem -= 1;
    } else if(nbItem){
        player->inventory[index].amount -= nbItem;

        if (player->inventory[index].amount <= 0) {
            player->inventory[index] = createItem(0, "", 0, 0, 0, 0);
            player->nbItem -= 1;
        }
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

void showInventory(Player *p){
    int i;
    for(i=0;i<10;i++){
        if(p->inventory[i].id != 0){
            if(p->inventory[i].type == CRAFT){
                printf("index : %d // nom : %s // quantite : %d\n",i,p->inventory[i].name,p->inventory[i].amount);
            }else if(p->inventory[i].type == OUTIL){
                printf("index : %d // nom : %s // durabilite : %0.1lf\n",i,p->inventory[i].name,p->inventory[i].durability);
            }else if(p->inventory[i].type == ARME){
                printf("index : %d // nom : %s // degats : %0.1lf // durabilite : %0.1lf\n",i,p->inventory[i].name,p->inventory[i].effect,p->inventory[i].durability);
            }else if(p->inventory[i].type == ARMURE){
                printf("index : %d // nom : %s // armure : %lf\n",i,p->inventory[i].name,p->inventory[i].effect);
            }else if(p->inventory[i].type == SOIN) {
                printf("index : %d // nom : %s // soin : %lf hp\n",i,p->inventory[i].name,p->inventory[i].effect);
            }
        }
    }
}

Player *initPlayer(Item *items){
    Player* player = malloc(sizeof(Player));

    player->hp = 100;
    player->hpMax = 100;
    player->exp = 0;
    player->lvl = 4;
    player->nbItem = 0;
    Item item = createItem(0,"",0,0,0,0);

    for (int i = 0; i < 10; ++i) {
        player->inventory[i] = item;
    }

    addInv(1, player, items);
    addInv(2, player, items);
    addInv(3, player, items);
    addInv(4, player, items);

    return player;
}

void levelUp(Player *p){
    int check = 0;
    int i;
    if(p->exp >=100 && p->lvl == 1 ){
        p->lvl = 2;
        p->exp -= 100;
        p->hpMax += 10;
        check = 1;
    }
    if(p->exp >=200 && p->lvl == 2 ){
        p->lvl = 3;
        p->exp -= 200;
        p->hpMax += 20;
        check = 1;
    }
    if(p->exp >=300 && p->lvl == 3 ){
        p->lvl = 4;
        p->exp -= 300;
        p->hpMax += 30;
        check = 1;
    }
    if(p->exp >=400 && p->lvl == 4 ){
        p->lvl = 5;
        p->exp -= 400;
        p->hpMax += 40;
        check = 1;
    }
    if(p->exp >=500 && p->lvl == 5 ){
        p->lvl = 6;
        p->exp -= 500;
        p->hpMax += 50;
        check = 1;
    }
    if(p->exp >=600 && p->lvl == 6 ){
        p->lvl = 7;
        p->exp -= 600;
        p->hpMax += 50;
        check = 1;
    }
    if(p->exp >=700 && p->lvl == 7 ){
        p->lvl = 8;
        p->exp -= 700;
        p->hpMax += 50;
        check = 1;
    }
    if(p->exp >=800 && p->lvl == 8 ){
        p->lvl = 9;
        p->exp -= 800;
        p->hpMax += 75;
        check = 1;
    }
    if(p->exp >=900 && p->lvl == 9 ){
        p->lvl = 10;
        p->exp = 0;
        p->hpMax += 75;
        check = 1;
    }
    if(check) {
        p->hp = p->hpMax;
        if (p->lvl == 10) {
            printf("BRAVO VOUS ETES NIVEAU MAX ! (%d)\n", 10);
        } else {
            printf("Felicitation vous avez gagner un niveau ! Vous etes desormais niveau : %d\n", p->lvl);
        }
        printf("(Appuyez sur entrer pour continuer)\n");
        fflush(stdin);
        scanf("%*c");
        printf("\n");
        fflush(stdin);
    }
}