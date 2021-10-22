#include "map.h"
#include "move.h"
#include "mobs.h"
#include "character.h"

int main() {
    srand( time( NULL ) );
    int i;
    int j;
    int height[3] = {7+(rand()%10),7+(rand()%10),7+(rand()%10)};
    int width[3] = {7+rand()%10,7+rand()%10,7+rand()%10};
    int **startPosition = malloc(sizeof(int*) *3);
    int ***map = malloc(sizeof(int**)*3);
    for(i=0;i<3;i++){
        startPosition[i] = malloc(sizeof(int) * 2);
        startPosition[i][0] = height[i]/2;
        startPosition[i][1] = width[i]/2;
        map[i] = initMap(width[i],height[i],i+1);
    }
    int game;
    int dir;
    Player* player = malloc(sizeof(Player));
    initPlayer(player);
    int *count = malloc(sizeof(int));
    int *actualMap = malloc(sizeof(int));
    *actualMap = 0;
    Mob *mobs = declareMobs(count);
    do{
        for(i = 0;i<height[*actualMap];i++){
            for(j=0;j<width[*actualMap];j++){
                printf("%3d",map[*actualMap][i][j]);
            }
            printf("\n");
        }
        printf("\n");
        printf("Que voulez vous faire ?\n   -Se deplacer (tapez 1)\n   -Attendre (tapez 2)\n   -Quitter et sauvegarer (tapez 3)\n");
        scanf("%d", &game);
        switch (game) {
            case 1:
                printf("Vers ou voulez vous aller ?\n   -Gauche ? (tapez 1)\n   -Droite ?(tapez 2)\n   -Haut ?(tapez 3)\n   -Bas ?(tapez 4)\n");
                scanf("%d",&dir);
                switch (dir) {
                    case 1:
                        move(map,height[*actualMap],width[*actualMap],startPosition,'l', actualMap);
                        break;
                    case 2:
                        move(map,height[*actualMap],width[*actualMap],startPosition,'r', actualMap);
                        break;
                    case 3:
                        move(map,height[*actualMap],width[*actualMap],startPosition,'u', actualMap);
                        break;
                    case 4:
                        move(map,height[*actualMap],width[*actualMap],startPosition,'d', actualMap);
                        break;
                    default:
                        printf("Ce n'est pas une direction valide\n");
                        break;
                }
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Rentrez un choix valide\n");
                break;
        }
    }while(game != 3);

    return 0;
}
