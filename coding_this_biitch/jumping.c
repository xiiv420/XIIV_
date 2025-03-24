#include "header.h"

void start_jump(Player *player) {
    if (player->onGround) {
        player->velocityY = -JUMP_STRENGTH;
        player->isJumping = 1;
        player->onGround = 0;
    }
}

void update_jump(Player *player) {
    if (!player->onGround) {
        player->y += player->velocityY;
        player->velocityY += GRAVITY;

        if (player->y >= SCREEN_HEIGHT - 50) {  
            player->y = SCREEN_HEIGHT - 50;
            player->onGround = 1;
            player->velocityY = 0;
        }
    }
}
