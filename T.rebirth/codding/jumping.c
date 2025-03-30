#include "header.h"

void start_jump(Player *player) {
    if (player->onGround && !player->isJumping) {
        player->velocityY = -JUMP_STRENGTH;  // Apply jump force
        player->isJumping = 1;  // Mark as jumping
        player->onGround = 0;   // Player is now in the air
    }
}

void update_jump(Player *player) {
    if (!player->onGround) {
        player->y += player->velocityY;  // Apply vertical movement

        // Apply gravity after movement
        player->velocityY += GRAVITY;  

        // If the player reaches the ground level
        int groundY = getGroundHeight(player->x + bg_x);
        if (groundY != -1 && player->y + 66 >= groundY) {
            player->y = groundY - 66 - 20 ;  // Correct position on ground
            player->velocityY = 0;     // Stop vertical movement
            player->onGround = 1;      // Mark as on the ground
            player->isJumping = 0;     // Ready to jump again
        }
    }
}
