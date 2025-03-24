#include "header.h"
#include <stdio.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    
    Player player;
    Enemy monster;
    Background bg;
    int running = 1, backgroundMoving = 0;

    // Initialize everything
    resetGame(&player, &monster, &bg);

    while (running) {
        handle_input(&running, &player);
        update_jump(&player);
        update_background(&bg, &backgroundMoving, &player, &monster);
        moveEnemy(&monster, player.x, backgroundMoving);
        attackPlayer(&monster, &player);

        // Check for game over
        if (player.health <= 0) {
            drawGameOver(screen, &running);
            resetGame(&player, &monster, &bg);
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));  // Clear screen
        SDL_BlitSurface(bg.background, NULL, screen, NULL);
        drawEnemy(&monster, screen);
        drawHealthBar(&player, screen);
        SDL_Flip(screen);
    }

    SDL_Quit();
    return 0;
}
