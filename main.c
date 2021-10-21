#include "character.h"

int main() {

    Player* player = malloc(sizeof(Player));
    initPlayer(player);

    printf("%d",player->inventory[1].id);
    removeItem(player,1);
    printf("%d",player->inventory[1].id);

    return 0;
}

