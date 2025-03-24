#include "constants.h"

SDL_Surface* background = NULL;
SDL_Surface* Idle_R = NULL;
SDL_Surface* Idle_L = NULL;
SDL_Surface* Run_R = NULL;
SDL_Surface* Run_L = NULL;

void run_background() {
    background = SDL_LoadBMP("background_map1.bmp");
    if (!background) {
        printf("Failed to load background: %s\n", SDL_GetError());
        exit(1);
    }
}

void run_playerSTANDING() {
    Idle_R = SDL_LoadBMP("Idle.bmp");
    if (!Idle_R) { printf("Failed to load Idle_R.bmp: %s\n", SDL_GetError()); exit(1); }

    Idle_L = SDL_LoadBMP("Idle_L.bmp");
    if (!Idle_L) { printf("Failed to load Idle_L.bmp: %s\n", SDL_GetError()); exit(1); }
}

void run_playerRUNNING() {
    Run_R = SDL_LoadBMP("Run.bmp");
    if (!Run_R) { printf("Failed to load Run_R.bmp: %s\n", SDL_GetError()); exit(1); }

    Run_L = SDL_LoadBMP("Run_L.bmp");
    if (!Run_L) { printf("Failed to load Run_L.bmp: %s\n", SDL_GetError()); exit(1); }
}


void update() {
    
    player.x += player.dx;
    if (player.isJumping) {
        player.y += player.dy;
        player.dy += GRAVITY;
        if (player.y >= SCREEN_HEIGHT - PLAYER_HEIGHT) {
            player.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
            player.isJumping = 0;
            player.dy = 0;
        }
    }
        // Prevent player from moving off-screen
    else if (player.x < 0) player.x = 0;
    else if (player.x > SCREEN_WIDTH - PLAYER_WIDTH) player.x = SCREEN_WIDTH - PLAYER_WIDTH;

}

void render() {
    SDL_Rect bgRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect playerRect = {player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT};
    SDL_BlitSurface(background, NULL, screen, &bgRect);
    SDL_BlitSurface(player.sprite, NULL, screen, &playerRect);
    SDL_Flip(screen);

}

int handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return 0;
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) return 0;
            if (event.key.keysym.sym == SDLK_d) {
                player.dx = SPEED;
                player.facingRight = 1;
            }
            if (event.key.keysym.sym == SDLK_q) {
                player.dx = -SPEED;
                player.facingRight = 0;
            }
            if (event.key.keysym.sym == SDLK_z && !player.isJumping) {
                player.dy = -JUMP_FORCE;
                player.isJumping = 1;
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_q)
                player.dx = 0;
        }
    }
    return 1;
}
