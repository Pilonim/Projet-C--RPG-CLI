//
// Created by jonat on 21/10/2021.
//

#include "move.h"

void checkCase(int ***map, int **position, int vertical, int horizontal, int *actualMap, Player *p, int **diedNpcs, int *nbDiedNpcs, Mob *mobs, int nbMobs, int *xpWin) {
    int verif = 0;
    char res[10];
    int i;
    int nextMap = map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal];
    if(nextMap == -1 || nextMap == 2){
        printf("Vous ne pouvez pas aller sur cette case\n");
    }else if (nextMap == 0) {
        map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
        position[*actualMap][0] += vertical;
        position[*actualMap][1] += horizontal;
        map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;
    }else if (nextMap >= 12) {
        *xpWin = fight(p,mobs,nextMap,nbMobs);
        if(*xpWin != -1){
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
            position[*actualMap][0] += vertical;
            position[*actualMap][1] += horizontal;
            for(i=0;i<*nbDiedNpcs;i++){
                if(diedNpcs[i][0] == position[*actualMap][0] && diedNpcs[i][1] == position[*actualMap][1]){
                    diedNpcs[i][3] = 15;
                    diedNpcs[i][4] = 1;
                }
            }
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;
        }else{
            return;
        }
    }else if (nextMap == -2 ){
        if(p->lvl >= 3) {
            *actualMap = *actualMap == 1 ? 0 : 1;
        }else{
            printf("Vous devez etre au moins niveau 3 pour franchir ce portail ! \n(entrer pour valider)");
            fflush(stdin);
            scanf("%*c");
            printf("\n");
            fflush(stdin);
        }
    }else if(nextMap == -3 ){
        if(p->lvl >= 7) {
            *actualMap = *actualMap == 1 ? 2 : 1;
        }else{
            printf("Vous devez etre au moins niveau 7 pour franchir ce portail ! \n(entrer pour valider)");
            fflush(stdin);
            scanf("%*c");
            printf("\n");
            fflush(stdin);
        }
    }else{
        if(nextMap == 3){
            strcpy(res,"herbe");
        }else if(nextMap == 4){
            strcpy(res,"pierre");
        }else if(nextMap == 5){
            strcpy(res,"sapin");
        }else if(nextMap == 6){
            strcpy(res,"lavande");
        }else if(nextMap == 7){
            strcpy(res,"fer");
        }else if(nextMap == 8){
            strcpy(res,"hetre");
        }else if(nextMap == 9){
            strcpy(res,"chanvre");
        }else if(nextMap == 10){
            strcpy(res,"diamant");
        }else if(nextMap == 11){
            strcpy(res,"chene");
        }
        verif = collect(p,nextMap);
        if(verif){
            printf("Vous avez recolter : %d %s\n", verif,res);
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
            position[*actualMap][0] += vertical;
            position[*actualMap][1] += horizontal;
            for(i=0;i<*nbDiedNpcs;i++){
                if(diedNpcs[i][0] == position[*actualMap][0] && diedNpcs[i][1] == position[*actualMap][1]){
                    diedNpcs[i][3] = 10;
                    diedNpcs[i][4] = 1;
                }
            }
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;
        }else{
            printf("Vous ne pouvez pas recolter cette ressource\n");
        };
    }
}
void move(int ***map, int height, int width, int **startPosition, char dir, int *actualMap, Player *p, int **diedNpcs, int *nbDiedNpcs, Mob *mobs, int nbMobs, int *xpWin) {
    int horizontal = 0;
    int vertical = 0;
    switch (dir) {
        case 'l':
            horizontal = -1;
            break;
        case 'r':
            horizontal = 1;
            break;
        case 'u':
            vertical = -1;
            break;
        case 'd':
            vertical = 1;
            break;
        default:
            printf("Direction non autorisee\n");
            return;
    }
    if (startPosition[*actualMap][0] + vertical < 0  || startPosition[*actualMap][1] + horizontal < 0){
        if(vertical){
            vertical = height-1;
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin);
        }else{
            horizontal = width-1;
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin);
        }
    }else if( startPosition[*actualMap][0] + vertical >= height  || startPosition[*actualMap][1] + horizontal >= width){
        if(vertical){
            vertical = -(height-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin);
        }else{
            horizontal = -(width-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin);
        }
    }else{
        checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin);
    }
}