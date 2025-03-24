#include "header.h"
#include <stdio.h>

void drawGameOver(SDL_Surface *screen, int *running) {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
    SDL_Surface *text = SDL_LoadBMP("gameover.bmp"); 
    SDL_BlitSurface(text, NULL, screen, NULL);
    SDL_Flip(screen);
    SDL_Delay(5000);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_r) {
                *running = 1;
                return;
            }
            if (event.key.keysym.sym == SDLK_q) {
                *running = 0;
            }
        }
    }
}
