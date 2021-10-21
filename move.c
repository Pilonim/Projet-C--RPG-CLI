//
// Created by jonat on 21/10/2021.
//

#include "move.h"

void checkCase(int **map, int *position, int vertical, int horizontal) {

    if(map[position[0] + vertical][position[1] + horizontal] == -1){
        printf("Vous ne pouvez pas aller sur cette case\n");
    }else if (map[position[0] + vertical][position[1] + horizontal] == 0) {
        map[position[0]][position[1]] = 0;
        position[0] += vertical;
        position[1] += horizontal;
        map[position[0]][position[1]] = 1;
    }else if (map[position[0] + vertical][position[1] + horizontal] >= 12) {
        //lancer combat
    }else{
        //lancer recolte
    }
}
void move(int **map, int height, int width, int *startPosition, int dir) {
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
            printf("Direction non autorisee");
            return;
    }
    if (startPosition[0] + vertical < 0  || startPosition[1] + horizontal < 0){
        if(vertical){
            vertical = height-1;
            checkCase(map, startPosition, vertical, horizontal);
        }else{
            horizontal = width-1;
            checkCase(map, startPosition, vertical, horizontal);
        }
    }else if( startPosition[0] + vertical >= height  || startPosition[1] + horizontal >= width){
        if(vertical){
            vertical = -(height-1);
            checkCase(map, startPosition, vertical, horizontal);
        }else{
            horizontal = -(width-1);
            checkCase(map, startPosition, vertical, horizontal);
        }
    }else{
        checkCase(map, startPosition, vertical, horizontal);
    }
}