#include "map.h"
#include "move.h"
#include "mobs.h"
#include "character.h"

int main() {
    int i;
    int j;
    int height = 10;
    int width = 10;
    int *startPosition = malloc(sizeof(int) *2);
    startPosition[0] = height/2;
    startPosition[1] = width/2;
    int **map = initMap(height,width,1);
    int game;
    int dir;
    Player* player = malloc(sizeof(Player));
    initPlayer(player);
    int *count = malloc(sizeof(int));
    Mob *mobs = declareMobs(count);
    for(i = 0 ;i< *(count);i++) {
        printf("%d %s %d %d %d\n", mobs[i].id, mobs[i].name, mobs[i].damages, mobs[i].xp, mobs[i].hp);
    }
    do{
        for(i = 0;i<height;i++){
            for(j=0;j<width;j++){
                printf("%3d",map[i][j]);
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
                        move(map,height,width,startPosition,'l');
                        break;
                    case 2:
                        move(map,height,width,startPosition,'r');
                        break;
                    case 3:
                        move(map,height,width,startPosition,'u');
                        break;
                    case 4:
                        move(map,height,width,startPosition,'d');
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
