#include "header.h"
#include <SDL/SDL.h>

extern SDL_Surface *screen;
extern int bg_x;

// Declare gameOverScreen function
int gameOverScreen(SDL_Surface *screen);

// Initialize player properties
void init_player(Player *player) {
    player->x = 300;
    player->y = getGroundHeight(300) - 66 - 20 ; // Dynamic ground height
    player->velocityY = 0;
    player->isJumping = 0;
    player->onGround = 1;
    player->speed = 5;
}

void update_player(Player *player) {
 // Raise the player position by 20px
    
    //call for game score  // Call this when the player earns points (based on game logic)

    int groundY = getGroundHeight(player->x + bg_x);  // Get platform height
    
    // Apply gravity if not on the ground
    if (!player->onGround) {
        player->velocityY += GRAVITY;  // Simulate gravity
    }

    // Update player position (falling)
    player->y += player->velocityY;

    // **Check if player falls off the screen**
    if (player->y > 600) {
        printf("Game Over! Player fell off the screen.\n");
        
        SDL_Rect fullScreen = {0, 0, screen->w, screen->h};
        
        for (int alpha = 0; alpha <= 255; alpha += 5) {
            SDL_FillRect(screen, &fullScreen, SDL_MapRGB(screen->format, 0, 0, 0));
            SDL_SetAlpha(screen, SDL_SRCALPHA, alpha);  // Doesn't work on screen but keeps syntax consistent
            SDL_Flip(screen);
            SDL_Delay(30);
        }
    
        int choice = gameOverScreen(screen);
        
        if (choice == 1) {
            init_player(player);   // Restart the game
        } else {
            exit(0);  // Quit the game
        }
    }
    

    // **Collision with ground/platforms**
    if (groundY != -1) {
        if (player->y + 66 > groundY && player->y < groundY) {
            player->y = groundY - 66;
            player->velocityY = 0;
            player->onGround = 1;
            player->isJumping = 0;
        } 
        else if (player->y + 66 < groundY) {
            player->onGround = 0;
        }
    } else {
        player->onGround = 0;
    }

    // **Prevent player from walking under platforms**
    if (player->onGround) {
        if (player->y + 66 <= groundY) {
            player->y = groundY - 66;
        }
    }
}

// Draw player as a red rectangle
void render_player(Player *player) {
    SDL_Rect playerRect = {player->x, player->y, 32, 66};
    Uint32 playerColor = SDL_MapRGB(screen->format, 255, 0, 0);
    SDL_FillRect(screen, &playerRect, playerColor);
}
