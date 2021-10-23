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

int **mapGen(int height, int width, int *npc, int npcSize, int ***diedNpcs, int **nbDiedNpcs, Mob *mobs, int *nbMobs){
    int i;
    int j;
    int startWidth;
    int value;
    int startHeight;
    int count = 0;
    int nbZero = 0;

    int **map = malloc(height * sizeof(int*));

    srand( time( NULL ) );
    for(i=0;i<height;i++){
        map[i] = malloc(width * sizeof(int));
    }
    for(i=0;i<height;i++){
        for(j=0;j<width;j++){
            map[i][j] = -1;
        }
    }
    startWidth = width/2;
    startHeight = height/2 ;
    map[startHeight][startWidth] = 0;
    while(nbZero < width*height*0.8){
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

    for(i=0;i<height;i++){

        for(j=0;j<width;j++){
            if(map[i][j] == 0){
                if(rand() % (npcSize-count) == 0){
                    map[i][j] = npc[count];
                    (*diedNpcs)[count][0] = i;
                    (*diedNpcs)[count][1] = j;
                    (*diedNpcs)[count][2] = npc[count];
                    (*diedNpcs)[count][4] = 0;
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
        if(i == height-1){
            i = -1;
        }
    }
    *nbDiedNpcs = malloc(sizeof(int));
    **nbDiedNpcs = count;
    return map;
}

int** initMap(int width, int height, int stage, int ***diedNpcs, int **nbDiedNpcs, Mob *mobs,int *nbMobs){
    srand( time( NULL ) );
    int stage1[5] = {3,4,5,0};
    int stage2[5] = {6,7,8,0};
    int stage3[5] = {9,10,11,0};
    int count = 0;
    int nbStage = 0;
    int i;
    int k;
    int find = 0;
    int nbNpc = ((height*width)/4);
    int *npc = malloc(nbNpc*sizeof(int));
    *diedNpcs = malloc(sizeof(int*) * nbNpc);
    for(i=0;i<nbNpc;i++){
        (*diedNpcs)[i] = malloc(sizeof(int)*5);
    }
    if(stage == 1) {
        npc[0] = 2;
        npc[1] = -2;
        i = 2;
    }else if(stage == 2){
        npc[0] = 2;
        npc[1] = -2;
        npc[2] = -3;
        i = 3;
    }else if(stage == 3){
        npc[0] = 2;
        npc[1] = -3;
        i = 2;
    }
    for(;i<nbNpc;i++){
        if(nbStage < 3 && stage == 1)
            npc[i] = stage1[nbStage];
        else if (nbStage < 3 && stage == 2)
            npc[i] = stage2[nbStage];
        else if(nbStage < 3 && stage == 3)
            npc[i] = stage3[nbStage];
        else {

            for (k = find; k < *nbMobs; k++) {
                if (mobs[k].stage == stage) {
                    npc[i] = mobs[k].id;
                    find = k+1;
                    break;
                }
                find += 1;
                if (find == (*nbMobs)) {
                    find = 0;
                    k = -1;
                }
            }
            printf("%d\n",find);
        }
        count+=1;
        if(count % ((nbNpc/4)-1) == 0){
            nbStage++;
        }
    }
    if(stage == 3)
        npc[nbNpc-1] = 99;
    shuffle(npc,nbNpc);
    return mapGen(height,width,npc,nbNpc,diedNpcs,nbDiedNpcs,mobs,nbMobs);
}

/*for (i = 0; i < height; i++) {
            for (j = 0; j < width; j++) {
                if (map[i][j] != -1) {
                    value = rand() % 4;
                    switch (value) {
                        case 0:
                            if (j != 0){
                                    if(map[i][j-1] == -1)
                                        map[i][j - 1] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (i != 0){
                                                if(map[i-1][j] == -1)
                                                    map[i - 1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j-1] == -1)
                                                            map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i+1][j] == -1)
                                                            map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                            if(map[i][j+1] == -1)
                                                map[i][j+1] = 0;
                                        break;
                                    case 2:
                                        if (i != height-1){
                                                if(map[i+1][j] == -1)
                                                    map[i+1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j+1] == -1)
                                                            map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i-1][j] == -1)
                                                            map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 1:
                            if (i != 0){
                                    if(map[i-1][j] == -1)
                                        map[i-1][j] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (j != width-1){
                                                if(map[i][j+1] == -1)
                                                    map[i][j+1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j-1] == -1)
                                                            map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i+1][j] == -1)
                                                            map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                            if(map[i+1][j] == -1)
                                                map[i+1][j] = 0;
                                        break;
                                    case 2:
                                        if (j != 0){
                                                if(map[i][j-1] == -1)
                                                    map[i][j-1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j+1] == -1)
                                                            map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i+1][j] == -1)
                                                            map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 2:
                            if (j != width-1){
                                    if(map[i][j+1] == -1)
                                        map[i][j+1] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (i != height-1){
                                                if(map[i+1][j] == -1)
                                                    map[i+1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j-1] == -1)
                                                            map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i-1][j] == -1)
                                                            map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                            if(map[i][j-1] == -1)
                                                map[i][j-1] = 0;
                                        break;
                                    case 2:
                                        if (i != 0){
                                                if(map[i-1][j] == -1)
                                                    map[i-1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j-1] == -1)
                                                            map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i+1][j] == -1)
                                                            map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 3:
                            if (i != height-1){
                                    if(map[i+1][j] == -1)
                                        map[i+1][j] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (j != 0){
                                                if(map[i][j-1] == -1)
                                                    map[i][j-1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j+1] == -1)
                                                            map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i-1][j] == -1)
                                                        map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                        if(map[i-1][j] == -1)
                                            map[i-1][j] = 0;
                                        break;
                                    case 2:
                                        if (j != width-1){
                                            if(map[i][j+1] == -1)
                                                map[i][j+1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                        if(map[i][j-1] == -1)
                                                            map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                        if(map[i-1][j] == -1)
                                                            map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                    }
                }
            }

        for (i = height-1; i >=0; i--) {
            for (j = width-1; j >=0 ; j--) {
                if (map[i][j] != -1) {
                    value = rand() % 4;
                    switch (value) {
                        case 0:
                            if (j != 0){
                                if(map[i][j-1] == -1)
                                    map[i][j - 1] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (i != 0){
                                            if(map[i-1][j] == -1)
                                                map[i - 1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j-1] == -1)
                                                        map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i+1][j] == -1)
                                                        map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                        if(map[i][j+1] == -1)
                                            map[i][j+1] = 0;
                                        break;
                                    case 2:
                                        if (i != height-1){
                                            if(map[i+1][j] == -1)
                                                map[i+1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j+1] == -1)
                                                        map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i-1][j] == -1)
                                                        map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 1:
                            if (i != 0){
                                if(map[i-1][j] == -1)
                                    map[i-1][j] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (j != width-1){
                                            if(map[i][j+1] == -1)
                                                map[i][j+1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j-1] == -1)
                                                        map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i+1][j] == -1)
                                                        map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                        if(map[i+1][j] == -1)
                                            map[i+1][j] = 0;
                                        break;
                                    case 2:
                                        if (j != 0){
                                            if(map[i][j-1] == -1)
                                                map[i][j-1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j+1] == -1)
                                                        map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i+1][j] == -1)
                                                        map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 2:
                            if (j != width-1){
                                if(map[i][j+1] == -1)
                                    map[i][j+1] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (i != height-1){
                                            if(map[i+1][j] == -1)
                                                map[i+1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j-1] == -1)
                                                        map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i-1][j] == -1)
                                                        map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                        if(map[i][j-1] == -1)
                                            map[i][j-1] = 0;
                                        break;
                                    case 2:
                                        if (i != 0){
                                            if(map[i-1][j] == -1)
                                                map[i-1][j] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j-1] == -1)
                                                        map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i+1][j] == -1)
                                                        map[i+1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                        case 3:
                            if (i != height-1){
                                if(map[i+1][j] == -1)
                                    map[i+1][j] = 0;
                            }else{
                                value = rand() % 3;
                                switch (value) {
                                    case 0:
                                        if (j != 0){
                                            if(map[i][j-1] == -1)
                                                map[i][j-1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j+1] == -1)
                                                        map[i][j+1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i-1][j] == -1)
                                                        map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                    case 1:
                                        if(map[i-1][j] == -1)
                                            map[i-1][j] = 0;
                                        break;
                                    case 2:
                                        if (j != width-1){
                                            if(map[i][j+1] == -1)
                                                map[i][j+1] = 0;
                                        }else{
                                            value = rand() % 2;
                                            switch (value) {
                                                case 0:
                                                    if(map[i][j-1] == -1)
                                                        map[i][j-1] = 0;
                                                    break;
                                                case 1:
                                                    if(map[i-1][j] == -1)
                                                        map[i-1][j] = 0;
                                                    break;
                                            }
                                        }
                                        break;
                                }
                            }
                            break;
                    }
                }
            }
        }
    }*/