#include "map.h"
#include "move.h"
#include "mobs.h"
#include "character.h"
#include "farm.h"

int main() {
    srand( time( NULL ) );
    int i;
    int j;
    int lock = 0;
    int choice;
    int height[3] = {7+(rand()%10),7+(rand()%10),7+(rand()%10)};
    int width[3] = {7+rand()%10,7+rand()%10,7+rand()%10};
    int **currentPos = malloc(sizeof(int*) * 3);
    int ***map = malloc(sizeof(int**)*3);
    int ***diedNpcs = malloc(sizeof(int**) * 3);
    int **nbDiedNpcs = malloc(sizeof(int*) * 3);
    int startPos[3][2] = {{height[0]/2,width[0]/2},{height[1]/2,width[1]/2},{height[2]/2,width[2]/2}};
    int *xpWin = malloc(sizeof(int));
    *xpWin = 0;
    int *count = malloc(sizeof(int));
    Mob *mobs = declareMobs(count);
    //printMobs(mobs,*count);
    for(i=0;i<3;i++){
        currentPos[i] = malloc(sizeof(int) * 2);
        currentPos[i][0] = height[i] / 2;
        currentPos[i][1] = width[i] / 2;
        map[i] = initMap(width[i],height[i],i+1,&(diedNpcs[i]),&(nbDiedNpcs[i]),mobs,count);
    }
    int game = 3;
    int dir;
    Player* player = malloc(sizeof(Player));
    int *actualMap = malloc(sizeof(int));
    initPlayer(player);
    *actualMap = 0;

    do{
        if(game != 3) {
            for (i = 0; i < (*nbDiedNpcs)[*actualMap]; i++) {
                if (diedNpcs[*actualMap][i][4] == 1) {
                    diedNpcs[*actualMap][i][3] -= 1;
                    if (diedNpcs[*actualMap][i][3] <= 0 &&
                        map[*actualMap][diedNpcs[*actualMap][i][0]][diedNpcs[*actualMap][i][1]] == 0) {
                        map[*actualMap][diedNpcs[*actualMap][i][0]][diedNpcs[*actualMap][i][1]] = diedNpcs[*actualMap][i][2];
                        diedNpcs[*actualMap][i][4] = 0;
                    }
                }
            }
        }
        for(i = 0;i<height[*actualMap];i++){
            for(j=0;j<width[*actualMap];j++){
                printf("%3d",map[*actualMap][i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("Que voulez vous faire ?\n   -Se deplacer (tapez 1)\n   -Attendre (tapez 2)\n   -Consulter son inventaire (tapez 3)\n   -Quitter et sauvegarer (tapez 4)\n");
        scanf("%d", &game);
        switch (game) {
            case 1:
                printf("Vers ou voulez vous aller ?\n   -Gauche ? (tapez 1)\n   -Droite ?(tapez 2)\n   -Haut ?(tapez 3)\n   -Bas ?(tapez 4)\n");
                scanf("%d",&dir);
                switch (dir) {
                    case 1:
                        move(map, height[*actualMap], width[*actualMap], currentPos, 'l', actualMap, player, diedNpcs[*actualMap], nbDiedNpcs[*actualMap], mobs, *count, xpWin);
                        break;
                    case 2:
                        move(map, height[*actualMap], width[*actualMap], currentPos, 'r', actualMap, player, diedNpcs[*actualMap], nbDiedNpcs[*actualMap], mobs, *count, xpWin);
                        break;
                    case 3:
                        move(map, height[*actualMap], width[*actualMap], currentPos, 'u', actualMap, player, diedNpcs[*actualMap], nbDiedNpcs[*actualMap], mobs, *count, xpWin);
                        break;
                    case 4:
                        move(map, height[*actualMap], width[*actualMap], currentPos, 'd', actualMap, player, diedNpcs[*actualMap], nbDiedNpcs[*actualMap], mobs, *count, xpWin);
                        break;
                    default:
                        printf("Ce n'est pas une direction valide\n");
                        break;
                }
                if(*xpWin == -1){
                    break;
                }
                if(*actualMap == 1 && player->lvl > 3 ){
                    *xpWin = 0;
                }else if(*actualMap == 2 && player->lvl > 7){
                    *xpWin = 0;
                }
                player->exp += *xpWin;
                *xpWin = 0;
                levelUp(player);
                break;
            case 2:
                lock +=1;
                if(lock >= 20){
                    printf("Vous etes bloque ?\n    1- Oui\n    2- Non\n");
                    scanf("%d",&choice);
                    switch (choice) {
                        case 1:
                            map[*actualMap][currentPos[*actualMap][0]][currentPos[*actualMap][1]] = 0;
                            map[*actualMap][startPos[*actualMap][0]][startPos[*actualMap][1]] = 1;
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
                showInventory(player);
                printf("(Appuyez sur entrer pour fermer l'inventaire)\n");
                fflush(stdin);
                scanf("%*c");
                printf("\n");
                fflush(stdin);
                break;
            case 4:
                break;
            default:
                printf("Rentrez un choix valide\n");
                break;
        }
    }while(game != 4 && *xpWin != -1);

    return 0;
}
