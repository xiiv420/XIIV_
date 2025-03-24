#include "header.h"

void move_player(Player *player, const Uint8 *keystate) {
    int speed = PLAYER_SPEED;

    if (keystate[SDLK_LEFT] || keystate[SDLK_q]) {
        player->x -= speed;
    }
    if (keystate[SDLK_RIGHT] || keystate[SDLK_d]) {
        player->x += speed;
    }

    if (player->x < LEFT_LIMIT) player->x = LEFT_LIMIT;
    if (player->x > RIGHT_LIMIT) player->x = RIGHT_LIMIT;
}
