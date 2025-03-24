#include "init.h"
#include <SDL/SDL.h>
#include <stdio.h>

SDL_Surface *init_SDL(int width, int height, int bpp) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL Initialization failed: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_Surface *screen = SDL_SetVideoMode(width, height, bpp, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to create screen: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    return screen;
}
