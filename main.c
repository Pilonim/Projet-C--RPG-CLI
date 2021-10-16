#include "map.c"


int main() {
    int i;
    int j;
    int height = 10;
    int width = 10;
    int **map = initMap(10,10);
    for(i = 0;i<height;i++){
        for(j=0;j<width;j++){
            printf("%3d",map[i][j]);
        }
        printf("\n");
    }



    return 0;
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