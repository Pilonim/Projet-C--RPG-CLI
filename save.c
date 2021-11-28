//
// Created by ferre on 29/10/2021.
//

#include "save.h"




void saveMap(FILE *fp, Game *game){
    fprintf(fp, "=== MAP ===\n");
    fprintf(fp, "-- ZONE 1 --\n");
    for (int k = 0; k < game->height[0]; ++k) {
        for (int i = 0; i < game->width[0]; ++i) {
            fprintf(fp, "%d", game->map[0][k][i]);
            if(i != game->width[0] - 1){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-- ZONE 2 --\n");
    for (int k = 0; k < game->height[1]; ++k) {
        for (int i = 0; i < game->width[1]; ++i) {
            fprintf(fp, "%d", game->map[1][k][i]);
            if(i != (game->width[1] - 1)){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-- ZONE 3 --\n");
    for (int k = 0; k < game->height[2]; ++k) {
        for (int i = 0; i < game->width[2]; ++i) {
            fprintf(fp, "%d", game->map[2][k][i]);
            if(i != (game->width[2] - 1)){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
}

void savePlayer(FILE *fp, Game *game){
    fprintf(fp, "=== PLAYER ===\n");
    fprintf(fp, "{%d}\n", game->player->lvl);
    fprintf(fp, "{%d}/{%d}\n", game->player->exp, (game->player->lvl * 100));
    fprintf(fp, "{%f}/{%f}\n", game->player->hp, game->player->hpMax);
    fputs("-- INVENTORY --\n", fp);
    int invSize = sizeof(game->player->inventory) / sizeof(Item);
    for (int k = 0; k < invSize ; ++k) {
        Item actualSlot = game->player->inventory[k];
        if(actualSlot.id == 0){
            fprintf(fp, "{0}@{0}@{0}\n");
        }else {
            fprintf(fp, "{%d}@{%d}@{%f}\n", actualSlot.amount, actualSlot.id, actualSlot.durability);
        }
    }
    fputs("-- STORAGE --\n", fp);
    int chestSize = game->pnj->chestSize;
    for (int k = 0; k < chestSize ; ++k) {
        Item actualSlot = game->pnj->chest[k];
        fprintf(fp, "{%d}@{%d}@{%f}\n", actualSlot.amount, actualSlot.id, actualSlot.durability);
    }
}

void saveNPCS(FILE *fp, Game *game){
    fputs("=== NPCS ===\n", fp);
    fprintf(fp, "{%d}/{%d}/{%d}\n", game->nbNpcs[0][0], game->nbNpcs[1][0], game->nbNpcs[2][0]);
    fprintf(fp, "-- ZONE 1 --\n");
    for (int k = 0; k < game->nbNpcs[0][0]; ++k) {
        for (int i = 0; i < 5; ++i) {
            fprintf(fp, "%d", game->npcs[0][k][i]);
            if(i != 4){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-- ZONE 2 --\n");
    for (int k = 0; k < game->nbNpcs[1][0]; ++k) {
        for (int i = 0; i < 5; ++i) {
            fprintf(fp, "%d", game->npcs[1][k][i]);
            if(i != 4){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "-- ZONE 3 --\n");
    for (int k = 0; k < game->nbNpcs[2][0]; ++k) {
        for (int i = 0; i < 5; ++i) {
            fprintf(fp, "%d", game->npcs[2][k][i]);
            if(i != 4){
                fprintf(fp, " ");
            }
        }
        fprintf(fp, "\n");
    }
}

void addToChestSave(PNJ *pnj, Item *it){
    Item* temp = malloc(sizeof(Item) * (pnj->chestSize + 1)); // 1

    for(int k = 0; k < pnj->chestSize; k++){ // 0
        temp[k] = pnj->chest[k];
    }

    temp[pnj->chestSize] = *it;
    free(pnj->chest);
    pnj->chestSize = pnj->chestSize + 1; //1
    pnj->chest = malloc(sizeof(Item) * pnj->chestSize); // 1

    for(int i = 0; i < pnj->chestSize; i++){ // 0
        pnj->chest[i] = temp[i];
    }

}

void loadTempZone1(FILE *fp, int *countZoneH, int *countZoneW){
    char buffer[255];
    fgets(buffer, sizeof(buffer), fp);
    if(!strcmp(buffer, "=== MAP ===\n")) {
        fgets(buffer, sizeof(buffer), fp);
        if (!strcmp(buffer, "-- ZONE 1 --\n")) {
            while (strcmp(buffer, "-- ZONE 2 --\n")) {
                fgets(buffer, sizeof(buffer), fp);
                if (!strcmp(buffer, "-- ZONE 2 --\n")) {
                    break;
                }
                char *list = strtok(buffer, " ");
                countZoneW[0] = 0;
                while (list != NULL) {
                    list = strtok(NULL, " ");
                    countZoneW[0] += 1;
                }
                countZoneH[0] += 1;
            }
        }

    }
}

void loadTempZone2(FILE *fp, int *countZoneH, int *countZoneW){
    char buffer[255];
    strcpy(buffer,"-- ZONE 2 --\n");
    if (!strcmp(buffer, "-- ZONE 2 --\n")) {

        while (strcmp(buffer, "-- ZONE 3 --\n")) {
            fgets(buffer, sizeof(buffer), fp);
            if (!strcmp(buffer, "-- ZONE 3 --\n")) {
                break;
            }
            char *list = strtok(buffer, " ");
            countZoneW[1] = 0;
            while (list != NULL) {
                list = strtok(NULL, " ");
                countZoneW[1] += 1;
            }
            countZoneH[1] += 1;
        }
    }

}

void loadTempZone3(FILE *fp, int *countZoneH, int *countZoneW){
    char buffer[255];
    strcpy(buffer,"-- ZONE 3 --\n");
    if (!strcmp(buffer, "-- ZONE 3 --\n")) {
        while (strcmp(buffer, "=== PLAYER ===\n")) {
            fgets(buffer, sizeof(buffer), fp);
            if (!strcmp(buffer, "=== PLAYER ===\n")) {
                break;
            }
            char *list = strtok(buffer, " ");
            countZoneW[2] = 0;
            while (list != NULL) {
                list = strtok(NULL, " ");
                countZoneW[2] += 1;
            }
            countZoneH[2] += 1;
        }
    }
}

void loadZone1(FILE *fp, int *countZoneH, int *countZoneW, int ***tempMap){
    char buffer[255];
    fgets(buffer, sizeof(buffer), fp);
    if(!strcmp(buffer, "=== MAP ===\n")) {
        fgets(buffer, sizeof(buffer), fp);
        if (!strcmp(buffer, "-- ZONE 1 --\n")) {
            int cptH = 0;
            int cptW = 0;
            while (strcmp(buffer, "-- ZONE 2 --\n")) {
                fgets(buffer, sizeof(buffer), fp);
                if (!strcmp(buffer, "-- ZONE 2 --\n")) {
                    break;
                }
                char *list = strtok(buffer, " ");
                while (list != NULL) {
                    tempMap[0][cptH][cptW] = atoi(list);
                    list = strtok(NULL, " ");
                    cptW++;
                }
                cptH++;
                cptW = 0;
            }
        }
    }
}

void loadZone2(FILE *fp, int *countZoneH, int *countZoneW, int ***tempMap){
    char buffer[255];
    strcpy(buffer,"-- ZONE 2 --\n");
    if(!strcmp(buffer, "-- ZONE 2 --\n")){
        int cptH = 0;
        int cptW = 0;
        while(strcmp(buffer, "-- ZONE 3 --\n")){
            fgets(buffer, sizeof(buffer), fp);
            if(!strcmp(buffer, "-- ZONE 3 --\n")){
                break;
            }
            char *list = strtok(buffer, " ");
            while(list != NULL){
                tempMap[1][cptH][cptW] = atoi(list);
                list = strtok(NULL, " ");
                cptW++;
            }
            cptH++;
            cptW = 0;
        }
    }
}

void loadZone3(FILE *fp, int *countZoneH, int *countZoneW, int ***tempMap){
    char buffer[255];
    strcpy(buffer,"-- ZONE 3 --\n");
    if(!strcmp(buffer, "-- ZONE 3 --\n")){
        int cptH = 0;
        int cptW = 0;
        while(strcmp(buffer, "=== PLAYER ===\n")){
            fgets(buffer, sizeof(buffer), fp);
            if(!strcmp(buffer, "=== PLAYER ===\n")){
                break;
            }
            char *list = strtok(buffer, " ");

            while(list != NULL){
                tempMap[2][cptH][cptW] = atoi(list);
                list = strtok(NULL, " ");
                cptW++;
            }
            cptH++;
            cptW = 0;
        }
    }
}

void loadPlayer(FILE *fp, Game *game){
    char buffer[255];
    strcpy(buffer,"=== PLAYER ===\n");
    if(!strcmp(buffer, "=== PLAYER ===\n")){
        fgets(buffer, sizeof(buffer), fp);
        sscanf(buffer,"{%d}", &game->player->lvl);
        fgets(buffer, sizeof(buffer), fp);
        sscanf(buffer, "{%d}/{%d}", &game->player->exp, &game->player->expMax);
        fgets(buffer, sizeof(buffer), fp);
        sscanf(buffer, "{%lf}/{%lf}", &game->player->hp, &game->player->hpMax);
        fgets(buffer, sizeof(buffer), fp);
        if(!strcmp(buffer, "-- INVENTORY --\n")){
            for (int k = 0; k < 10; ++k) {
                fgets(buffer, sizeof(buffer), fp);
                Item *it = malloc(sizeof(Item));
                sscanf(buffer, "{%d}@{%d}@{%lf}", &it->id, &it->amount, &it->durability);
                game->player->inventory[k] = *it;
            }
        }
        fgets(buffer, sizeof(buffer), fp);
        if(!strcmp(buffer, "-- STORAGE --\n")){
            int cpt = 0;
            while(strcmp(buffer, "=== NPCS ===\n")){
                fgets(buffer, sizeof(buffer), fp);
                if(!strcmp(buffer, "=== NPCS ===\n")){
                    break;
                }
                Item *it = malloc(sizeof(Item));
                sscanf(buffer, "{%d}@{%d}@{%lf}", &it->amount, &it->id, &it->durability);
                if(it->amount != 0) {
                    strcpy(it->name,game->items[it->id-1].name);
                    it->type = game->items[it->id-1].type;
                    it->maxDurability = game->items[it->id-1].maxDurability;
                    it->effect = game->items[it->id-1].effect;
                    addToChestSave(game->pnj, it);
                }

            }
        }
    }
}

void loadNPCS(FILE *fp, Game *game, int ***tempNPCS){
    char buffer[255];
    strcpy(buffer,"-- ZONE 1 --\n");
        if (!strcmp(buffer, "-- ZONE 1 --\n")) {
            for (int j = 0; j < game->nbNpcs[0][0]; ++j) {
                fgets(buffer, sizeof(buffer), fp);
                sscanf(buffer, "%d %d %d %d %d", &tempNPCS[0][j][0], &tempNPCS[0][j][1], &tempNPCS[0][j][2], &tempNPCS[0][j][3], &tempNPCS[0][j][4]);
            }
        }
        fgets(buffer, sizeof(buffer), fp);
        if (!strcmp(buffer, "-- ZONE 2 --\n")) {
            for (int j = 0; j < game->nbNpcs[1][0]; ++j) {
                fgets(buffer, sizeof(buffer), fp);
                sscanf(buffer, "%d %d %d %d %d", &tempNPCS[1][j][0], &tempNPCS[1][j][1], &tempNPCS[1][j][2], &tempNPCS[1][j][3], &tempNPCS[1][j][4]);
            }
        }
        fgets(buffer, sizeof(buffer), fp);
        if (!strcmp(buffer, "-- ZONE 3 --\n")) {
            for (int j = 0; j < game->nbNpcs[2][0]; ++j) {
                fgets(buffer, sizeof(buffer), fp);
                sscanf(buffer, "%d %d %d %d %d", &tempNPCS[2][j][0], &tempNPCS[2][j][1], &tempNPCS[2][j][2], &tempNPCS[2][j][3], &tempNPCS[2][j][4]);
            }
        }

}


void save(Game *game){
    FILE *fp = NULL;

    char path[255] = "../save/";
    strcat(path, game->playerName);
    strcat(path, "_save.txt");
    fopen_s(&fp, path, "w");

    saveMap(fp, game);
    savePlayer(fp, game);
    saveNPCS(fp, game);

    fclose(fp);
}

void load(Game **game){
    FILE *fp = NULL;
    char buffer[255];
    int count = 0;
    char path[255] = "../save/";
    strcat(path, (*game)->playerName);
    strcat(path, "_save.txt");
    fopen_s(&fp, path, "r");
    int ***tempMap = malloc(sizeof(int**)*3);

    int *countZoneH = malloc(sizeof(int) * 3);
    int *countZoneW = malloc(sizeof(int) * 3);

    for(int i = 0; i < 3; i++){
        countZoneW[i] = 0;
        countZoneH[i] = 0;
    }
    loadTempZone1(fp, countZoneH, countZoneW);
    tempMap[0] = malloc(sizeof(int *) * countZoneH[0]);
    for (int k = 0; k < countZoneH[0]; ++k) {
        tempMap[0][k] = malloc(sizeof(int) * countZoneW[0]);
    }
    loadTempZone2(fp, countZoneH, countZoneW);
    tempMap[1] = malloc(sizeof(int *) * countZoneH[1]);
    for (int k = 0; k < countZoneH[1]; ++k) {
        tempMap[1][k] = malloc(sizeof(int) * countZoneW[1]);
    }
    loadTempZone3(fp, countZoneH, countZoneW);
    tempMap[2] = malloc(sizeof(int *) * countZoneH[2]);
    for (int k = 0; k < countZoneH[2]; ++k) {
        tempMap[2][k] = malloc(sizeof(int) * countZoneW[2]);
    }
    rewind(fp);
    loadZone1(fp, countZoneH, countZoneW, tempMap);
    loadZone2(fp, countZoneH, countZoneW, tempMap);
    loadZone3(fp, countZoneH, countZoneW, tempMap);
    (*game)->map = tempMap;
    for (int i = 0; i < 3; ++i) {
        (*game)->width[i] = countZoneW[i];
        (*game)->height[i] = countZoneH[i];
        (*game)->startPos[i][0] = ((*game)->height[i] / 2);
        (*game)->startPos[i][1] = ((*game)->width[i] / 2);

        for (int k = 0; k < (*game)->height[i]; ++k) {
            for (int j = 0; j < (*game)->width[i]; ++j) {
                if((*game)->map[i][k][j] == 1){
                    (*game)->currentPos[i][0] = k;
                    (*game)->currentPos[i][1] = j;
                }
            }
        }

    }



    loadPlayer(fp, (*game));

    int ***tempNPCS = malloc(sizeof(int**)*3);
    strcpy(buffer,"=== NPCS ===\n");
    if(!strcmp(buffer, "=== NPCS ===\n")) {
        fgets(buffer, sizeof(buffer), fp);
        sscanf(buffer, "{%d}/{%d}/{%d}", &(*game)->nbNpcs[0][0], &(*game)->nbNpcs[1][0], &(*game)->nbNpcs[2][0]);

        tempNPCS[0] = malloc(sizeof(int *) * (*game)->nbNpcs[0][0]);
        tempNPCS[1] = malloc(sizeof(int *) * (*game)->nbNpcs[1][0]);
        tempNPCS[2] = malloc(sizeof(int *) * (*game)->nbNpcs[2][0]);

        for (int k = 0; k < 3; ++k) {
            for (int i = 0; i < (*game)->nbNpcs[k][0]; ++i) {
                tempNPCS[k][i] = malloc(sizeof(int) * 5);
            }
        }

        loadNPCS(fp, (*game), tempNPCS);
        (*game)->npcs = tempNPCS;
    }



    fclose(fp);


}
