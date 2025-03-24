#include "header.h"

void update_background(Background *bg, int *backgroundMoving, Player *player, Enemy *monster) {
    if (player->x >= RIGHT_LIMIT) {
        *backgroundMoving = 1;  
        player->x = RIGHT_LIMIT;
        monster->pos.x = monster->pos.x;  
    }

    if (*backgroundMoving) {
        bg->bgX -= PLAYER_SPEED;
        monster->pos.x -= MONSTER_SLOW_SPEED;

        if (bg->bgX % SCREEN_WIDTH == 0) {
            *backgroundMoving = 0;
        }
    }
}
