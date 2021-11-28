//
// Created by jonat on 16/10/2021.
//


#include "../headers/map.h"
void shuffle(int *array, int n)
{
    srand( time( NULL ) );
    if (n > 1)
    {
        int i;
        for (i = 0; i < n - 1; i++)
        {
            int j = rand() % n;
            int t = array[j];
            array[j] = array[i];
            array[i] = t;
        }
    }
}

int **mapGen(Game **game, int stage, int *npc, int npcSize){
    int i;
    int j;
    int startWidth;
    int startHeight;
    int count = 0;
    int nbZero = 0;

    int **map = malloc((*game)->height[stage-1] * sizeof(int*));

    srand( time( NULL ) );
    for(i=0;i<(*game)->height[stage-1];i++){
        map[i] = malloc((*game)->width[stage-1] * sizeof(int));
    }
    for(i=0;i<(*game)->height[stage-1];i++){
        for(j=0;j<(*game)->width[stage-1];j++){
            map[i][j] = -1;
        }
    }
    startWidth = (*game)->width[stage-1]/2;
    startHeight = (*game)->height[stage-1]/2 ;
    map[startHeight][startWidth] = 0;
    while(nbZero < (*game)->width[stage-1]*(*game)->height[stage-1] * 0.7){
        i = rand()%(*game)->height[stage-1];
        j = rand()%(*game)->width[stage-1];
        if (i == 0){
            if(j == 0){
                if( (map[i+1][j] == 0 || map[i][j+1] == 0) && map[i][j] == -1)  {
                    nbZero += 1;
                    map[i][j] = 0;
                }
            }else if(j == (*game)->width[stage-1]-1){
                if( ( map[i+1][j] == 0 || map[i][j-1] == 0 ) && map[i][j] == -1)  {
                    nbZero += 1;
                    map[i][j] = 0;
                }
            }else{
                if( (map[i+1][j] == 0 || map[i][j-1] == 0 || map[i][j+1] == 0) && map[i][j] == -1)  {
                    nbZero += 1;
                    map[i][j] = 0;
                }
            }
        }else if(i == (*game)->height[stage-1]-1){
            if(j == 0){
                if( (map[i-1][j] == 0 ||  map[i][j+1] == 0) && map[i][j] == -1)  {
                    nbZero += 1;
                    map[i][j] = 0;
                }
            }else if(j == (*game)->width[stage-1]-1){
                if( (map[i-1][j] == 0 ||  map[i][j-1] == 0) && map[i][j] == -1)  {
                    nbZero += 1;
                    map[i][j] = 0;
                }
            }else{
                if( (map[i-1][j] == 0 || map[i][j-1] == 0 || map[i][j+1] == 0) && map[i][j] == -1)  {
                    nbZero += 1;
                    map[i][j] = 0;
                }
            }
        }else if(j == 0){
            if( (map[i-1][j] == 0 || map[i+1][j] == 0 || map[i][j+1] == 0) && map[i][j] == -1)  {
                nbZero += 1;
                map[i][j] = 0;
            }
        }else if(j == (*game)->width[stage-1]-1){
            if( (map[i-1][j] == 0 || map[i+1][j] == 0 || map[i][j-1] == 0) && map[i][j] == -1)  {
                nbZero += 1;
                map[i][j] = 0;
            }
        }else{
            if( (map[i-1][j] == 0 || map[i+1][j] == 0 || map[i][j-1] == 0 || map[i][j+1] == 0) && map[i][j] == -1)  {
                nbZero += 1;
                map[i][j] = 0;
            }
        }
    }
    count = 0;

    map[startHeight][startWidth] = stage == 1?1:0;
    //map[startHeight][startWidth] = 1;
    for(i=0;i<(*game)->height[stage-1];i++){
        for(j=0;j<(*game)->width[stage-1];j++){
            if(map[i][j] == 0){
                if(rand() % (npcSize-count) == 0){
                    map[i][j] = npc[count];
                    (*game)->npcs[stage - 1][count][0] = i;
                    (*game)->npcs[stage - 1][count][1] = j;
                    (*game)->npcs[stage - 1][count][2] = npc[count];
                    (*game)->npcs[stage - 1][count][3] = 0;
                    (*game)->npcs[stage - 1][count][4] = 0;
                    if((stage == 2 && npc[count] == -2) || (stage == 3 && npc[count] == -3)) {
                        (*game)->currentPos[stage-1][0] = i;
                        (*game)->currentPos[stage-1][1] = j+1;
                        if(j == (*game)->width[stage-1]-1){
                            map[i][j-1] = 1;
                        }else{
                            map[i][j+1] = 1;
                        }
                    }
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
        if(i == (*game)->height[stage-1]-1){
            i = -1;
        }
    }
    (*game)->nbNpcs[stage - 1][0] = count;
    return map;
}

int** initMap(Game **game, int stage){
    srand( time( NULL ) );
    int stage1[5] = {3,4,5,0};
    int stage2[5] = {6,7,8,0};
    int stage3[5] = {9,10,11,0};
    int count = 0;
    int nbStage = 0;
    int i;
    int k;
    int nbMobsStaged = 0;
    int random;
    int *mobsStaged;
    int find = 0;
    int nbNpc = (( ((*game)->height[stage-1] )* ((*game)->width[stage-1]))/4);
    int *npc = malloc(nbNpc*sizeof(int));
    (*game)->npcs[stage - 1] = malloc(sizeof(int*) * nbNpc);
    for(i=0;i<nbNpc;i++){
        (*game)->npcs[stage - 1][i] = malloc(sizeof(int) * 5);
    }
    for(i=0;i<*((*game)->mobCount);i++) {
        if ((*game)->mobs[i].stage == stage) {
            nbMobsStaged += 1;
        }
    }
    count = nbMobsStaged;
    mobsStaged = malloc(sizeof(int) * nbMobsStaged);
    for(i=0;i<*((*game)->mobCount);i++){
        if((*game)->mobs[i].stage == stage) {
            mobsStaged[count - 1] = (*game)->mobs[i].id;
            count -= 1;
        }
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
            random = rand() % nbMobsStaged;
            npc[i] = mobsStaged[random];
        }
        count+=1;
        if(count % ((nbNpc/4)-1) == 0){
            nbStage++;
        }
    }
    if(stage == 3)
        npc[nbNpc-1] = 99;
    shuffle(npc,nbNpc);
    return mapGen(game, stage, npc, nbNpc);
}

void printMap(Game *game){
    int i;
    int j;
    for(i = 0;i<game->height[*(game->currentMap)]; i++){
        for(j=0;j<game->width[*(game->currentMap)]; j++){

            printf("%3d",game->map[*(game->currentMap)][i][j]);
        }
        printf("\n");
    }
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