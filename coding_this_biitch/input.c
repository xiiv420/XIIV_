#include "header.h"

void handle_input(int *running, Player *player) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                start_jump(player);
            }
        }
    }

    const Uint8 *keystate = SDL_GetKeyState(NULL);
    move_player(player, keystate);
}
