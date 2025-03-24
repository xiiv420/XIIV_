#include "header.h"

void drawHealthBar(Player *player, SDL_Surface *screen) {
    SDL_Rect healthBar = {10, 10, player->health * 4, 20}; 
    SDL_FillRect(screen, &healthBar, SDL_MapRGB(screen->format, 255, 0, 0));
}
