#include "../headers/map.h"
#include "../headers/move.h"
#include "../headers/mobs.h"
#include "../headers/character.h"
#include "../headers/farm.h"
#include "../headers/craft.h"
#include "../headers/save.h"

int main() {
    /*Initialisation des variables */
    srand( time( NULL ) );
    Game *game = malloc(sizeof(Game));
    int i;
    int lock = 0;
    char name[255];

    printf("Votre nom ?\n");
    fgets(name,255,stdin);
    if(name[strlen(name)-1] == '\n'){
        name[strlen(name)-1] = '\0';
    }
    strcpy(game->playerName,name);

    FILE *fp = NULL;
    char path[255] = "save/";
    strcat(path, game->playerName);
    strcat(path, "_save.txt");
    fopen_s(&fp, path, "r");
    game->currentPos = malloc(sizeof(int *) * 3);
    game->currentMap = malloc(sizeof(int));
    game->xpWin = malloc(sizeof(int));
    game->nbNpcs = malloc(sizeof(int *) * 3);
    int choice;
    game->onPortal = malloc(sizeof(int));
    *(game->onPortal) = 0;
    int gameState = 3;
    int dir;
    game->pnj = malloc(sizeof(PNJ));
    initPNJ(game->pnj);
    *(game->xpWin) = 0;
    game->itemCount = malloc(sizeof(int));
    game->craftCount = malloc(sizeof(int));
    game->mobCount = malloc(sizeof(int));
    game->isCraftable = malloc(sizeof(int) * *game->craftCount);
    game->mobs = declareMobs(game->mobCount);
    game->crafts = declareCraft(game->craftCount);
    game->items = declareItem(game->itemCount);
    game->player = initPlayer(game->items);
    if(fp){
        fclose(fp);
        for (i = 0; i < 3; i++) {
            game->currentPos[i] = malloc(sizeof(int) * 2);
            game->nbNpcs[i] = malloc(sizeof(int));
        }
        load(&game);
    }else {
        for (i = 0; i < 3; i++) {
            game->height[i] = 7 + (rand() % 10);
            game->width[i] = 7 + (rand() % 10);
            game->startPos[i][0] = game->height[i] / 2;
            game->startPos[i][1] = game->width[i] / 2;
        }
        game->map = malloc(sizeof(int **) * 3);
        game->npcs = malloc(sizeof(int **) * 3);
        *(game->currentMap) = 0;
        for (i = 0; i < 3; i++) {
            game->currentPos[i] = malloc(sizeof(int) * 2);
            game->currentPos[i][0] = game->height[i] / 2;
            game->currentPos[i][1] = game->width[i] / 2;
            game->nbNpcs[i] = malloc(sizeof(int));
            game->map[i] = initMap(&game, i + 1);
        }
    }
    /*Debut boucle de jeu*/
    do{
        /*Affichage de la map*/
        respawn(game);
        printMap(game);
        printf("\n");

        /*Choix du joueur*/
        printf("Que voulez vous faire ?\n   -Se deplacer (tapez 1)\n   -Attendre (tapez 2)\n   -Consulter son inventaire (tapez 3)\n   -Consulter son statut (tapez 4)\n");
        if(*(game->onPortal)){
            printf("   -Prendre le portail (tapez 5)\n   -Quitter et sauvegarer (tapez -1)\n");
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
                        move(game, 'l');
                        break;
                    case 2:
                        move(game, 'r');
                        break;
                    case 3:
                        move(game, 'u');
                        break;
                    case 4:
                        move(game, 'd');
                        break;
                    default:
                        printf("Ce n'est pas une direction valide\n");
                        break;
                }

                /*Verifications post combat*/
                if(*(game->xpWin) == -1){
                    playerDie(game);
                    save(game);
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
                            game->currentPos[*(game->currentMap)][0] = game->startPos[*(game->currentMap)][0];
                            game->currentPos[*(game->currentMap)][1] = game->startPos[*(game->currentMap)][1];
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
                save(game);
                break;
            case 4:
                showPlayer(game);
                break;
            case 5:
                /* Changement de map via portail*/
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
    }while(gameState != -1);

    return 0;
}
