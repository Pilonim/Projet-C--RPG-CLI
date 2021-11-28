//
// Created by jonat on 21/10/2021.
//

#include "../headers/move.h"

void chest(Game *game){
    int menuChoice;
    int choice;
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
}

void moveToPnj(Game *game){
    int menuChoice;

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
            if(isCraftable(game->player,game->crafts,*(game->craftCount),game->items,game->currentMap,game)){
                printf("Que veux-tu craft ?\n");
                do{
                    scanf("%d",&menuChoice);
                }while(menuChoice < 1 || menuChoice > 25);
                craft(game->player, game->crafts, menuChoice, game->items, game);
            }
            printf("(entrer pour valider)\n");
            fflush(stdin);
            scanf("%*c");
            printf("\n");
            fflush(stdin);
            break;
        case 3:
            do {
                chest(game);
            }while(menuChoice != 0);
            break;
        default:
            printf("Alo ?");
    }
}

void moveToFight(Game *game, int nextMap, int vertical, int horizontal) {
    int i;
    *(game->xpWin) = fight(game->player,game->mobs,nextMap,*(game->mobCount),game);
    if(*(game->xpWin) != -1) {
        game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
        game->currentPos[*(game->currentMap)][0] += vertical;
        game->currentPos[*(game->currentMap)][1] += horizontal;
        for (i = 0; i < *(game->nbNpcs[*(game->currentMap)]); i++) {
            if (game->npcs[*(game->currentMap)][i][0] == game->currentPos[*(game->currentMap)][0] &&
                game->npcs[*(game->currentMap)][i][1] == game->currentPos[*(game->currentMap)][1]) {
                game->npcs[*(game->currentMap)][i][3] = 15;
                game->npcs[*(game->currentMap)][i][4] = 1;
            }
        }
        game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;
        *(game->onPortal) = 0;
    }
}

void teleport(Game *game, int vertical, int horizontal, int minLvl, int portal){
    int i;
    if(game->player->lvl >= minLvl) {
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

        *(game->onPortal) = portal;
    }else{
        printf("Vous devez etre au moins niveau %d pour franchir ce portail ! \n(entrer pour valider)",minLvl);
        fflush(stdin);
        scanf("%*c");
        printf("\n");
        fflush(stdin);
    }
}

int checkRes(Game *game, int nextMap, int vertical, int horizontal){
    char res[10];
    int verif = 0;
    int i;

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
    }
}
void checkCase(Game *game, int vertical, int horizontal) {

    int nextMap = game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0] + vertical][game->currentPos[*(game->currentMap)][1] + horizontal];
    if(nextMap == -1){
        printf("Vous ne pouvez pas aller sur cette case\n");
    }else if(nextMap == 2){
        moveToPnj(game);
    }else if (nextMap == 0) {
        game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
        game->currentPos[*(game->currentMap)][0] += vertical;
        game->currentPos[*(game->currentMap)][1] += horizontal;
        game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 1;
        *(game->onPortal) = 0;
    }else if (nextMap >= 12) {
        moveToFight(game,nextMap,vertical,horizontal);
    }else if (nextMap == -2 ){
        teleport(game,vertical,horizontal,3,1);
    }else if(nextMap == -3 ){
        teleport(game,vertical,horizontal,7,2);
    }else{
        checkRes(game,nextMap,vertical,horizontal);
    }
}

void move(Game *game, char dir) {
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
            checkCase(game, vertical, horizontal);
        }else{
            horizontal = game->width[*(game->currentMap)]-1;
            checkCase(game, vertical, horizontal);
        }
    }else if( game->currentPos[*(game->currentMap)][0] + vertical >= game->height[*(game->currentMap)]  || game->currentPos[*(game->currentMap)][1] + horizontal >= game->width[*(game->currentMap)]){
        if(vertical){
            vertical = -(game->height[*(game->currentMap)]-1);
            checkCase(game, vertical, horizontal);
        }else{
            horizontal = -(game->width[*(game->currentMap)]-1);
            checkCase(game, vertical, horizontal);
        }
    }else{
        checkCase(game, vertical, horizontal);
    }
}

