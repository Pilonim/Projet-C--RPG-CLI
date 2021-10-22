//
// Created by jonat on 21/10/2021.
//

#include "move.h"

void checkCase(int ***map, int **position, int vertical, int horizontal, int *actualMap, Player *p) {
    int verif = 0;
    char res[10];

    if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == -1 || map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 2){
        printf("Vous ne pouvez pas aller sur cette case\n");
    }else if (map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 0) {
        map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
        position[*actualMap][0] += vertical;
        position[*actualMap][1] += horizontal;
        map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;
    }else if (map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] >= 12) {
        //lancer combat
    }else if (map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == -2 ){
        *actualMap = *actualMap == 1?0:1;
    }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == -3 ){
        *actualMap = *actualMap == 1?2:1;
    }else{
        if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 3){
            strcpy(res,"herbe");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 4){
            strcpy(res,"pierre");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 5){
            strcpy(res,"sapin");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 6){
            strcpy(res,"lavande");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 7){
            strcpy(res,"fer");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 8){
            strcpy(res,"hetre");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 9){
            strcpy(res,"chanvre");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 10){
            strcpy(res,"diamant");
        }else if(map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal] == 11){
            strcpy(res,"chene");
        }
        verif = collect(p,map[*actualMap][position[*actualMap][0] + vertical][position[*actualMap][1] + horizontal]);
        if(verif){
            printf("Vous avez recolter : %d %s\n", verif,res);
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 0;
            position[*actualMap][0] += vertical;
            position[*actualMap][1] += horizontal;
            map[*actualMap][position[*actualMap][0]][position[*actualMap][1]] = 1;
        }else{
            printf("Vous ne pouvez pas recolter cette ressource\n");
        };
    }
}
void move(int ***map, int height, int width, int **startPosition, char dir, int *actualMap, Player *p) {
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
            checkCase(map, startPosition, vertical, horizontal, actualMap, p);
        }else{
            horizontal = width-1;
            checkCase(map, startPosition, vertical, horizontal, actualMap, p);
        }
    }else if( startPosition[*actualMap][0] + vertical >= height  || startPosition[*actualMap][1] + horizontal >= width){
        if(vertical){
            vertical = -(height-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap, p);
        }else{
            horizontal = -(width-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap, p);
        }
    }else{
        checkCase(map, startPosition, vertical, horizontal, actualMap, p);
    }
}