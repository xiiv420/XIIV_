#include "cleanup.h"

void cleanup(SDL_Surface *screen) {
    if (screen) {
        SDL_FreeSurface(screen);
    }
    SDL_Quit();
}
