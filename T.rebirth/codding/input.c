#include "header.h"
#include <SDL/SDL.h>

void handle_input(int *running, Player *player) {
    SDL_Event event;
    
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            *running = 0;
        }
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_SPACE && player->onGround) {
                player->velocityY = -JUMP_STRENGTH;  // Use the new jump strength
                player->onGround = 0;
            }
        }
    }

    // SDL 1.2: Get key state for movement
    SDL_PumpEvents();
    const Uint8 *keystate = SDL_GetKeyState(NULL);

    // Move left (Q key)
    if (keystate[SDLK_q]) {
        if (player->x > 200) {
            player->x -= player->speed;
        } else if (bg_x > 0) {
            bg_x -= player->speed;  // Move background FASTER to match player
        }
    }

    // Move right (D key)
    if (keystate[SDLK_d]) {
        if (player->x < 500) {
            player->x += player->speed;
        } else if (bg_x < 1600) { // Adjust max value if needed
            bg_x += player->speed;  // Move background FASTER to match player
        }
    }

    // Clamp player position
    if (player->x < 200) player->x = 200;
    if (player->x > 500) player->x = 500;
}
