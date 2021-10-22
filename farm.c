//
// Created by jonat on 21/10/2021.
//

#include "farm.h"



int collect(Player *p, int caseValue){
    srand(time(NULL));
    int axe[3] = {4,14,25};
    int pickaxe[3] = {2,12,23};
    int billhook[3] = {3,13,24};
    int itemId;
    int i;
    int j;
    int k;
    int times = 1+rand()%3;
    switch (caseValue) {
        case 3:
            itemId = 7;
            break;
        case 4:
            itemId = 6;
            break;
        case 5:
            itemId = 5;
            break;
        case 6:
            itemId = 18;
            break;
        case 7:
            itemId = 17;
            break;
        case 8:
            itemId = 16;
            break;
        case 9:
            itemId = 29;
            break;
        case 10:
            itemId = 28;
            break;
        case 11:
            itemId = 27;
            break;
        default:
            printf("Qu'est ce que je fais la ?");
            break;
    }
    for(j=0;j<10;j++){
        for(i=(caseValue/3)-1;i<3;i++){
            if(caseValue == 4 || caseValue == 7 || caseValue == 10){
                if(pickaxe[i] == p->inventory[j].id){
                    for(k=0;k<times;k++){
                        addInv(itemId,p);
                    }
                    if(itemId < 10 ){
                        p->inventory[j].durability -= (p->inventory[j].durability*0.1);
                    }else if (itemId < 20){
                        p->inventory[j].durability -= (p->inventory[j].durability*0.2);
                    }else{
                        p->inventory[j].durability -= (p->inventory[j].durability*0.4);
                    }
                    return times;
                }
            }else if(caseValue == 5 || caseValue == 8 || caseValue == 11){
                if(axe[i] == p->inventory[j].id){
                    for(k=0;k<times;k++){
                        addInv(itemId,p);
                    }
                    if(itemId < 10 ){
                        p->inventory[j].durability -= (p->inventory[j].durability*0.1);
                    }else if (itemId < 20){
                        p->inventory[j].durability -= (p->inventory[j].durability*0.2);
                    }else{
                        p->inventory[j].durability -= (p->inventory[j].durability*0.4);
                    }
                    return times;
                }
            }else if(caseValue == 3 || caseValue == 6 || caseValue == 9){
                if(billhook[i] == p->inventory[j].id){
                    for(k=0;k<times;k++){
                        addInv(itemId,p);
                    }
                    if(itemId < 10 ){
                        p->inventory[j].durability -= (p->inventory[j].durability*0.1);
                    }else if (itemId < 20){
                        p->inventory[j].durability -= (p->inventory[j].durability*0.2);
                    }else{
                        p->inventory[j].durability -= (p->inventory[j].durability*0.4);
                    }
                    return times;
                }
            }
        }
    }
    return 0;

}