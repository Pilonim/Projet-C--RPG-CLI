#include "map.h"


int main() {
    int i;
    int j;
    int height = 20;
    int width = 20;
    int **map = initMap(height,width,1);
    for(i = 0;i<height;i++){
        for(j=0;j<width;j++){
            printf("%3d",map[i][j]);
        }
        printf("\n");
    }
    return 0;
}
