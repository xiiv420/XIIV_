#include "constants.h"

SDL_Surface* screen = NULL;
Player player;

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        return 1;
    }

    player.x = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;  // Center the player
    player.y = SCREEN_HEIGHT - PLAYER_HEIGHT;      // Place on the ground    
    player.dx = 0;
    player.dy = 0;
    player.isJumping = 0;
    player.facingRight = 1;
    player.isRunning = 0;

    run_background();
    run_playerSTANDING();
    player.sprite = Idle_R;
    if (!player.sprite) { 
        printf("Error: Player sprite is NULL\n"); 
        exit(1); 
    }

    run_playerRUNNING();

    int running = 1;
    while (running) {
        running = handle_events();
        update();
        render();
        SDL_Delay(16);
    }

    SDL_FreeSurface(Idle_R);
    SDL_FreeSurface(Idle_L);
    SDL_FreeSurface(Run_R);
    SDL_FreeSurface(Run_L);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}
