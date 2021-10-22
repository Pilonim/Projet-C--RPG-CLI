//
// Created by jonat on 21/10/2021.
//

#include "move.h"

void checkCase(int ***map, int **position, int vertical, int horizontal, int *actualMap) {

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
        //lancer recolte
    }
}
void move(int ***map, int height, int width, int **startPosition, char dir, int *actualMap) {
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
            checkCase(map, startPosition, vertical, horizontal, actualMap);
        }else{
            horizontal = width-1;
            checkCase(map, startPosition, vertical, horizontal, actualMap);
        }
    }else if( startPosition[*actualMap][0] + vertical >= height  || startPosition[*actualMap][1] + horizontal >= width){
        if(vertical){
            vertical = -(height-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap);
        }else{
            horizontal = -(width-1);
            checkCase(map, startPosition, vertical, horizontal, actualMap);
        }
    }else{
        checkCase(map, startPosition, vertical, horizontal, actualMap);
    }
}