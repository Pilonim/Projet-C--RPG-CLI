//
// Created by jonat on 21/10/2021.
//

#include "move.h"

/*void checkCase(int ***map, int **position, int vertical, int horizontal, int *actualMap, Player *p, int **diedNpcs, int *nbDiedNpcs, Mob *mobs, int nbMobs, int *xpWin, int *onPortal, Item *items) {
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
        *onPortal = 0;
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
            *onPortal = 0;
        }else{
            return;
        }
    }else if (nextMap == -2 ){
        if(p->lvl >= 3) {
            //*actualMap = *actualMap == 1 ? 0 : 1;
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
            position[*actualMap][0] += vertical;
            position[*actualMap][1] += horizontal;
            for(i=0;i<*nbDiedNpcs;i++){
                if(diedNpcs[i][0] == position[*actualMap][0] && diedNpcs[i][1] == position[*actualMap][1]){
                    diedNpcs[i][3] = 0;
                    diedNpcs[i][4] = 1;
                    //printf("J sui la npcs[i][3]:%d npcs[i][4]:%d\n",npcs[i][3],npcs[i][4]);
                }
            }
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;

            *onPortal = 1;
        }else{
            printf("Vous devez etre au moins niveau 3 pour franchir ce portail ! \n(entrer pour valider)");
            fflush(stdin);
            scanf("%*c");
            printf("\n");
            fflush(stdin);
        }
    }else if(nextMap == -3 ){
        if(p->lvl >= 7) {
            //*actualMap = *actualMap == 1 ? 2 : 1;
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
            position[*actualMap][0] += vertical;
            position[*actualMap][1] += horizontal;
            for(i=0;i<*nbDiedNpcs;i++){
                if(diedNpcs[i][0] == position[*actualMap][0] && diedNpcs[i][1] == position[*actualMap][1]){
                    diedNpcs[i][3] = 0;
                    diedNpcs[i][4] = 1;
                }
            }
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;
            *onPortal = 2;
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
        verif = collect(p,nextMap,items);
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
            *onPortal = 0;
        }else{
            printf("Vous ne pouvez pas recolter cette ressource\n");
        };
    }
}
void move(int ***map, int height, int width, int **startPosition, char dir, int *actualMap, Player *p, int **diedNpcs, int *nbDiedNpcs, Mob *mobs, int nbMobs, int *xpWin, int *onPortal, Item *items) {
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
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin, onPortal,items);
        }else{
            horizontal = width-1;
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin, onPortal,items);
        }
    }else if( startPosition[*actualMap][0] + vertical >= height  || startPosition[*actualMap][1] + horizontal >= width){
        if(vertical){
            vertical = -(height-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin, onPortal,items);
        }else{
            horizontal = -(width-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin, onPortal,items);
        }
    }else{
        checkCase(map, startPosition, vertical, horizontal, actualMap, p, diedNpcs, nbDiedNpcs, mobs, nbMobs, xpWin, onPortal,items);
    }
}*/

void checkCase2(Game *game, int vertical, int horizontal) {
    int verif = 0;
    int menuChoice;
    int choice;
    char res[10];
    int i;
    int nextMap = game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0] + vertical][game->currentPos[*(game->currentMap)][1] + horizontal];
    if(nextMap == -1){
        printf("Vous ne pouvez pas aller sur cette case\n");
    }else if(nextMap == 2){
        printf("Bonjour aventurier, quelle action souhaitez vous effectuer ?\n   1-Reparer ?\n   2-Crafter ?\n   3-Acceder au stockage ?\n");
        do{
            scanf("%d",&menuChoice);
        }while(menuChoice < 1 || menuChoice > 3);
        switch (menuChoice) {
            case 1:
                repairPlayerItems(game->player);
                printf("Vous avez reparer vos items !\n");
                break;
            case 2:
                isCraftable(game->player,game->crafts,*(game->craftCount),game->items,game->currentMap,game);
                printf("Que veux-tu craft ?\n");
                do{
                    scanf("%d",&menuChoice);
                }while(menuChoice < 1 || menuChoice > 25);
                craft(game->player, game->crafts, menuChoice, game->items, game);
                printf("(entrer pour valider)\n");
                fflush(stdin);
                scanf("%*c");
                printf("\n");
                fflush(stdin);
                break;
            case 3:
                do {
                    printf("Votre chest : \n");
                    showChest(game->pnj);
                    printf("Veux-tu deposer ou retirer ?\n   1-Retirer\n   2-Deposer\n   0-Quitter\n");
                    do {
                        scanf("%d", &menuChoice);
                    } while (menuChoice < 0 || menuChoice > 2);
                    switch (menuChoice) {
                        case 0:
                            break;
                        case 1:
                            printf("Que voulez-vous retirer ?\n");
                            do {
                                scanf("%d", &choice);
                            } while (choice < 0 || choice > game->pnj->chestSize);
                            removeFromChest(game->pnj, game->player, choice, game->items);
                            break;
                        case 2:
                            showInventory(game->player);
                            printf("Que voulez-vous deposer ?\n");
                            do {
                                scanf("%d", &choice);
                            } while (choice < 0 || choice > 9);
                            addToChest(game->pnj, game->player, choice);
                            break;
                        default:
                            printf("Alo 2?");
                    }
                }while(menuChoice != 0);
                break;
            default:
                printf("Alo ?");
        }
    }else if (nextMap == 0) {
        game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
        game->currentPos[*(game->currentMap)][0] += vertical;
        game->currentPos[*(game->currentMap)][1] += horizontal;
        game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;
        *(game->onPortal) = 0;
    }else if (nextMap >= 12) {
        *(game->xpWin) = fight(game->player,game->mobs,nextMap,*(game->mobCount),game);
        if(*(game->xpWin) != -1){
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
            game->currentPos[*(game->currentMap)][0] += vertical;
            game->currentPos[*(game->currentMap)][1] += horizontal;
            for(i=0;i<*(game->nbNpcs[*(game->currentMap)]); i++){
                if(game->npcs[*(game->currentMap)][i][0] == game->currentPos[*(game->currentMap)][0] && game->npcs[*(game->currentMap)][i][1] == game->currentPos[*(game->currentMap)][1]){
                    game->npcs[*(game->currentMap)][i][3] = 15;
                    game->npcs[*(game->currentMap)][i][4] = 1;
                }
            }
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;
            *(game->onPortal) = 0;
        }else{
            return;
        }
    }else if (nextMap == -2 ){
        if(game->player->lvl >= 3) {
            //*(game->currentMap) = *(game->currentMap) == 1 ? 0 : 1;
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
            game->currentPos[*(game->currentMap)][0] += vertical;
            game->currentPos[*(game->currentMap)][1] += horizontal;
            for(i=0;i<*(game->nbNpcs[*(game->currentMap)]); i++){
                if(game->npcs[*(game->currentMap)][i][0] == game->currentPos[*(game->currentMap)][0] && game->npcs[*(game->currentMap)][i][1] == game->currentPos[*(game->currentMap)][1]){
                    game->npcs[*(game->currentMap)][i][3] = 0;
                    game->npcs[*(game->currentMap)][i][4] = 1;
                    //printf("J sui la game->npcs[*(game->currentMap)][i][3]:%d game->npcs[*(game->currentMap)][i][4]:%d\n",game->npcs[*(game->currentMap)][i][3],game->npcs[*(game->currentMap)][i][4]);
                }
            }
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;

            *(game->onPortal) = 1;
        }else{
            printf("Vous devez etre au moins niveau 3 pour franchir ce portail ! \n(entrer pour valider)");
            fflush(stdin);
            scanf("%*c");
            printf("\n");
            fflush(stdin);
        }
    }else if(nextMap == -3 ){
        if(game->player->lvl >= 7) {
            //*(game->currentMap) = *(game->currentMap) == 1 ? 2 : 1;
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
            game->currentPos[*(game->currentMap)][0] += vertical;
            game->currentPos[*(game->currentMap)][1] += horizontal;
            for(i=0;i<*(game->nbNpcs[*(game->currentMap)]); i++){
                if(game->npcs[*(game->currentMap)][i][0] == game->currentPos[*(game->currentMap)][0] && game->npcs[*(game->currentMap)][i][1] == game->currentPos[*(game->currentMap)][1]){
                    game->npcs[*(game->currentMap)][i][3] = 0;
                    game->npcs[*(game->currentMap)][i][4] = 1;
                }
            }
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;
            *(game->onPortal) = 2;
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
        verif = collect(game->player,nextMap,game->items);
        if(verif){
            printf("Vous avez recolter : %d %s\n", verif,res);
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
            game->currentPos[*(game->currentMap)][0] += vertical;
            game->currentPos[*(game->currentMap)][1] += horizontal;
            for(i=0;i<*(game->nbNpcs[*(game->currentMap)]); i++){
                if(game->npcs[*(game->currentMap)][i][0] == game->currentPos[*(game->currentMap)][0] && game->npcs[*(game->currentMap)][i][1] == game->currentPos[*(game->currentMap)][1]){
                    game->npcs[*(game->currentMap)][i][3] = 10;
                    game->npcs[*(game->currentMap)][i][4] = 1;
                }
            }
            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;
            *(game->onPortal) = 0;
        }else{
            printf("Vous ne pouvez pas recolter cette ressource\n");
        };
    }
}

void move2(Game *game, char dir) {
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
    if (game->currentPos[*(game->currentMap)][0] + vertical < 0  || game->currentPos[*(game->currentMap)][1] + horizontal < 0){
        if(vertical){
            vertical = game->height[*(game->currentMap)]-1;
            checkCase2(game,vertical,horizontal);
        }else{
            horizontal = game->width[*(game->currentMap)]-1;
            checkCase2(game,vertical,horizontal);
        }
    }else if( game->currentPos[*(game->currentMap)][0] + vertical >= game->height[*(game->currentMap)]  || game->currentPos[*(game->currentMap)][1] + horizontal >= game->width[*(game->currentMap)]){
        if(vertical){
            vertical = -(game->height[*(game->currentMap)]-1);
            checkCase2(game,vertical,horizontal);
        }else{
            horizontal = -(game->width[*(game->currentMap)]-1);
            checkCase2(game,vertical,horizontal);
        }
    }else{
        checkCase2(game,vertical,horizontal);
    }
}

