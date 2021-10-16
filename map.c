//
// Created by jonat on 16/10/2021.
//


#include "map.h"
void shuffle(int *array, size_t n)
{
    srand( time( NULL ) );
    if (n > 1)
    {
        size_t i;
        for (i = 0; i < n - 1; i++)
        {
            size_t j = rand() % n;
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int **mapGen(int height, int width, int *npc, int npcSize){
    int i;
    int j;
    int turn;
    int max;
    int startWidth;
    int value;
    int startHeight;
    int count = 0;
    int nbZero = 0;

    int **map = malloc(height*sizeof(int*));

    srand( time( NULL ) );
    for(i=0;i<height;i++){
        map[i] = malloc(width*sizeof(int));
    }
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            map[i][j] = -1;
        }
    }
    startWidth = width/2;
    startHeight = height/2 ;
    map[startHeight][startWidth] = 0;
    max = height > width?height:width;
    for(turn=0;turn < max*max*max;turn++) {
        i = rand()%height;
        j = rand()%width;
        if(map[i][j] == 0) {

            value = rand() % 4;
            switch (value) {
                case 0:
                    if (j != 0){
                        if(map[i][j-1] == -1) {
                            map[i][j - 1] = 0;
                            nbZero++;
                        }
                    }
                    break;
                case 1:
                    if (i != 0){
                        if(map[i-1][j] == -1) {
                            map[i - 1][j] = 0;
                            nbZero++;
                        }
                    }
                    break;
                case 2:
                    if (j != width-1) {
                        if (map[i][j + 1] == -1) {
                            map[i][j + 1] = 0;
                            nbZero++;
                        }
                    }
                    break;
                case 3:
                    if (i != height-1){
                        if(map[i+1][j] == -1) {
                            map[i + 1][j] = 0;
                            nbZero++;
                        }
                    }
                    break;
            }
        }
    }
    count = 0;
    map[startHeight][startWidth] = 1;
    printf("%d\n",nbZero);
    for(i=0;i<height;i++){

        for(j=0;j<width;j++){
            if(map[i][j] == 0){
                if(rand() % (npcSize-count) == 0){
                    map[i][j] = npc[count];
                    count++;
                }
                if(count == npcSize || count == nbZero){
                    break;
                }
            }
        }
        if(count == npcSize || count == nbZero){
            break;
        }
        if(i == height-1 && count != npcSize){
            i = -1;
        }
    }
    printf("\n%d\n",count);
    return map;
}

int** initMap(int width, int height, int stage){
    srand( time( NULL ) );
    int stage1[5] = {2,3,4,5,0};
    int count = 0;
    int nbStage = 1;
    int i;
    int nbNpc = ((height*width)/4);
    int *npc = malloc(nbNpc*sizeof(int));
    npc[0] = 2;
    npc[1] = -2;
    for(i=2;i<nbNpc;i++){
        if(nbStage < 4)
            npc[i] = stage1[nbStage];
        else
            npc[i] = rand()%(98-12) + 12 ;
        count+=1;
        if(count % ((nbNpc/4)-1) == 0){
            nbStage++;
        }
    }
    for(i=0;i<nbNpc;i++){
        printf("%3d",npc[i]);
    }
    shuffle(npc,nbNpc);
    return mapGen(height,width,npc,nbNpc);
}

