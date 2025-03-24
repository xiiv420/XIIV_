#include "header.h"

void moveEnemy(Enemy *e, int player_x, int backgroundMoving) {
    if (!backgroundMoving) {
        if (player_x > e->pos.x) {
            e->pos.x += MONSTER_SPEED;
        }
    }
}

void attackPlayer(Enemy *e, Player *player) {
    if (abs(player->x - e->pos.x) < 30 && e->attackCooldown <= 0) {
        player->health -= 10;
        e->attackCooldown = 800;  // 0.8s cooldown
    }
    e->attackCooldown -= (e->attackCooldown > 0) ? 1 : 0;
}

void drawEnemy(Enemy *e, SDL_Surface *screen) {
    SDL_BlitSurface(e->sprite, NULL, screen, &e->pos);
}
