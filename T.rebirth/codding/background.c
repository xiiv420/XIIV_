#include <SDL/SDL.h>

SDL_Surface *background = NULL;
SDL_Surface *screen = NULL;





int initBackground() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL init error: %s\n", SDL_GetError());
        return -1;
    }

    screen = SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Screen error: %s\n", SDL_GetError());
        SDL_Quit(); // Cleanup here
        return -1;
    }

    background = SDL_LoadBMP("/home/T.rebirth/images/lvl2.bmp");
    if (!background) {
        printf("Image error: %s\n", SDL_GetError());
        SDL_FreeSurface(screen);
        SDL_Quit(); // Cleanup here
        return -1;
    }

    return 0;
}



// Render the background at a specific x-offset (for scrolling)
void renderBackground(int bg_x) {
    SDL_Rect srcRect = {bg_x, 0, 800, 600};
    SDL_Rect destRect = {0, 0, 800, 600};
    SDL_BlitSurface(background, &srcRect, screen, &destRect); // Blit only, no flip
}

// Cleanup resources
void cleanupBackground() {
    if (background != NULL) {
        SDL_FreeSurface(background);  // Free the background image
    }
    SDL_Quit();  // Quit SDL subsystems
}
