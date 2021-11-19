#include "map.h"
#include "move.h"
#include "mobs.h"
#include "character.h"
#include "farm.h"
#include "craft.h"

int main() {
    srand( time( NULL ) );
    Game *game = malloc(sizeof(Game));
    int i;
    int j;
    int lock = 0;
    game->onPortal = malloc(sizeof(int));
    *(game->onPortal) = 0;
    int choice;
    for(i=0;i<3;i++){
        game->height[i] = 7+(rand()%10);
        game->width[i] = 7+(rand()%10);
        game->startPos[i][0] = game->height[i]/2;
        game->startPos[i][1] = game->width[i]/2;
    }
    /*int height[3] = {7+rand()%10,7+rand()%10,7+rand()%10};
    int width[3] = {7+rand()%10,7+rand()%10,7+rand()%10};*/
    game->currentPos = malloc(sizeof(int*) * 3);
    game->map = malloc(sizeof(int**)*3);
    game->npcs = malloc(sizeof(int**) * 3);
    game->nbNpcs = malloc(sizeof(int*) * 3);
    //game->startPos = {{height[0]/2,width[0]/2},{height[1]/2,width[1]/2},{height[2]/2,width[2]/2}};
    game->xpWin = malloc(sizeof(int));
    *(game->xpWin) = 0;
    game->mobCount = malloc(sizeof(int));
    game->currentMap = malloc(sizeof (int));
    *(game->currentMap) = 0;
    game->mobs = declareMobs(game->mobCount);
    //printMobs(mobs,*count);
    for(i=0;i<3;i++){
        game->currentPos[i] = malloc(sizeof(int) * 2);
        game->currentPos[i][0] = game->height[i] / 2;
        game->currentPos[i][1] = game->width[i] / 2;
        game->nbNpcs[i] = malloc(sizeof(int));
        game->map[i] = initMap2(&game,i+1);
        //game->map[i] = initMap(game->width[i],game->height[i],i+1,&(game->npcs[i]),game->nbNpcs[i],game->mobs,game->mobCount,game->currentPos[i]);
    }
    int gameState = 3;
    int dir;
    game->pnj = malloc(sizeof(PNJ));
    initPNJ(game->pnj);
    game->itemCount = malloc(sizeof(int));
    game->craftCount = malloc(sizeof(int));
    game->isCraftable = malloc(sizeof(int) * *game->craftCount);
    game->crafts = declareCraft(game->craftCount);
    game->items = declareItem(game->itemCount);
    game->player = initPlayer(game->items);
    do{
        if(gameState != 3) {
            for (i = 0; i < game->nbNpcs[*(game->currentMap)][0]; i++) {
                if (game->npcs[*(game->currentMap)][i][4] == 1) {
                    game->npcs[*(game->currentMap)][i][3] -= 1;
                    if (game->npcs[*(game->currentMap)][i][3] <= 0 &&
                        game->map[*(game->currentMap)][game->npcs[*(game->currentMap)][i][0]][game->npcs[*(game->currentMap)][i][1]] == 0) {
                        game->map[*(game->currentMap)][game->npcs[*(game->currentMap)][i][0]][game->npcs[*(game->currentMap)][i][1]] = game->npcs[*(game->currentMap)][i][2];
                        game->npcs[*(game->currentMap)][i][4] = 0;
                    }
                }
            }
        }
        for(i = 0;i<game->height[*(game->currentMap)]; i++){
            for(j=0;j<game->width[*(game->currentMap)]; j++){
                printf("%3d",game->map[*(game->currentMap)][i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("Que voulez vous faire ?\n   -Se deplacer (tapez 1)\n   -Attendre (tapez 2)\n   -Consulter son inventaire (tapez 3)\n");
        if(*(game->onPortal)){
            printf("   -Prendre le portail (tapez 4)\n   -Quitter et sauvegarer (tapez -1)\n");
        }else{
            printf("   -Quitter et sauvegarer (tapez -1)\n");
        }
        scanf("%d", &gameState);

        switch (gameState) {
            case 1:
                printf("Vers ou voulez vous aller ?\n   -Gauche ? (tapez 1)\n   -Droite ?(tapez 2)\n   -Haut ?(tapez 3)\n   -Bas ?(tapez 4)\n");
                scanf("%d",&dir);
                switch (dir) {
                    case 1:
                        //move(game->map, game->height[*(game->currentMap)], game->width[*(game->currentMap)], game->currentPos, 'l', game->currentMap, game->player, game->npcs[*(game->currentMap)], game->nbNpcs[*(game->currentMap)], game->mobs, *(game->mobCount), game->xpWin, game->onPortal, game->items);
                        move2(game,'l');
                        break;
                    case 2:
                        //move(game->map, game->height[*(game->currentMap)], game->width[*(game->currentMap)], game->currentPos, 'r', game->currentMap, game->player, game->npcs[*(game->currentMap)], game->nbNpcs[*(game->currentMap)], game->mobs, *(game->mobCount), game->xpWin, game->onPortal, game->items);
                        move2(game,'r');
                        break;
                    case 3:
                        //move(game->map, game->height[*(game->currentMap)], game->width[*(game->currentMap)], game->currentPos, 'u', game->currentMap, game->player, game->npcs[*(game->currentMap)], game->nbNpcs[*(game->currentMap)], game->mobs, *(game->mobCount), game->xpWin, game->onPortal, game->items);
                        move2(game,'u');
                        break;
                    case 4:
                        //move(game->map, game->height[*(game->currentMap)], game->width[*(game->currentMap)], game->currentPos, 'd', game->currentMap, game->player, game->npcs[*(game->currentMap)], game->nbNpcs[*(game->currentMap)], game->mobs, *(game->mobCount), game->xpWin, game->onPortal, game->items);
                        move2(game,'d');
                        break;
                    default:
                        printf("Ce n'est pas une direction valide\n");
                        break;
                }
                if(*(game->xpWin) == -1){
                    break;
                }
                if(*(game->currentMap) == 1 && game->player->lvl > 3 ){
                    *(game->xpWin) = 0;
                }else if(*(game->currentMap) == 2 && game->player->lvl > 7){
                    *(game->xpWin) = 0;
                }
                game->player->exp += *(game->xpWin);
                *(game->xpWin) = 0;
                levelUp(game->player);
                break;
            case 2:
                lock +=1;
                if(lock >= 20){
                    lock = 0;
                    printf("Vous etes bloque ?\n    1- Oui\n    2- Non\n");
                    scanf("%d",&choice);
                    switch (choice) {
                        case 1:
                            game->map[*(game->currentMap)][game->currentPos[*(game->currentMap)][0]][game->currentPos[*(game->currentMap)][1]] = 0;
                            game->map[*(game->currentMap)][game->startPos[*(game->currentMap)][0]][game->startPos[*(game->currentMap)][1]] = 1;
                            break;
                        case 2:
                            break;
                        default:
                            printf("Saisir une reponse valide");
                            break;

                    }
                }
                break;
            case 3:
                showInventory(game->player);
                printf("(Appuyez sur entrer pour fermer l'inventaire)\n");
                fflush(stdin);
                scanf("%*c");
                printf("\n");
                fflush(stdin);
                break;
            case -1:
                break;
            case 4:
                if(*(game->onPortal)){
                    printf("Voulez-vous changer de map ?\n   1-Oui\n   2-Non\n");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            *(game->currentMap) = *(game->onPortal) == 1? *(game->currentMap) == 0?1:0 : *(game->currentMap) == 1?2:1;
                            break;
                        case 2:
                            break;
                        default:
                            printf("Rentrez un choix valide\n");
                    }
                }else{
                    printf("Rentrez un choix valide\n");
                }
                break;
            default:
                printf("Rentrez un choix valide\n");
                break;
        }
    }while(gameState != -1 && *(game->xpWin) != -1);

    return 0;
}
