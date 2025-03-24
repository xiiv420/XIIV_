#include <SDL/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define SPEED 5
#define JUMP_FORCE 15
#define GRAVITY 1

#define FRAME_WIDTH 128  // Width of a single frame in the sprite sheet
#define FRAME_HEIGHT 128 // Height of a single frame
#define FRAME_COUNT 10    // Number of frames in the running animation

int currentFrame = 0;
int frameTimer = 0; // Controls animation speed

// Player structure
typedef struct {
    int x, y;
    int dx, dy;
    int isJumping;
    int facingRight;
    int isRunning;
    int bgX;  // Background X offset (moved from global)
    SDL_Surface* sprite;
} Player;


// SDL Variables
SDL_Surface* screen = NULL;
SDL_Surface* background = NULL;
SDL_Surface* Idle_R = NULL;
SDL_Surface* Idle_L = NULL;
SDL_Surface* Run_R = NULL;
SDL_Surface* Run_L = NULL;

Player player;

// Load background
void run_background() {
    background = SDL_LoadBMP("background_map1.bmp");
    if (!background) {
        printf("Failed to load background: %s\n", SDL_GetError());
        exit(1);
    }
}

// Load player standing and running sprites
void run_playerSTANDING() {
    Idle_R = SDL_LoadBMP("Idle.bmp");
    if (!Idle_R) {
        printf("❌ Failed to load Idle_R: %s\n", SDL_GetError());
        exit(1);
    } else {
        printf("✅ Loaded Idle_R successfully!\n");
    }

    Idle_L = SDL_LoadBMP("Idle_L.bmp");
    if (!Idle_L) {
        printf("❌ Failed to load Idle_L: %s\n", SDL_GetError());
        exit(1);
    } else {
        printf("✅ Loaded Idle_L successfully!\n");
    }
}


void run_playerRUNNING() {
    Run_R = SDL_LoadBMP("Run.bmp");
    if (!Run_R) {
        printf("Failed to load Run_R: %s\n", SDL_GetError());
        exit(1);
    }

    Run_L = SDL_LoadBMP("Run_L.bmp");
    if (!Run_L) {
        printf("Failed to load Run_L: %s\n", SDL_GetError());
        exit(1);
    }
}

// Update movement
void update(Player* player, int* bgX) {
    int bgWidth = 1600;  // Actual background width
    int SCREEN_RIGHT_EDGE = 500;
    int SCREEN_LEFT_EDGE = 300;

    if (player->dx > 0) {  
        if (player->x < SCREEN_RIGHT_EDGE || *bgX <= -(bgWidth - SCREEN_WIDTH)) {
            player->x += player->dx;
        } else {
            *bgX -= player->dx;  // Scroll background
        }
    } 
    else if (player->dx < 0) { 
        if (player->x > SCREEN_LEFT_EDGE || *bgX >= 0) {
            player->x += player->dx;
        } else {
            *bgX -= player->dx;  // Scroll background
        }
    }

    // **Ensure player stays visible**
    if (player->x < 0) player->x = 0;
    if (player->x > SCREEN_WIDTH - PLAYER_WIDTH) player->x = SCREEN_WIDTH - PLAYER_WIDTH;

    // **Ensure background stays within valid range**
    if (*bgX > 0) *bgX = 0;
    if (*bgX < -(bgWidth - SCREEN_WIDTH)) *bgX = -(bgWidth - SCREEN_WIDTH);
}





// Render graphics
void render(SDL_Surface* screen, SDL_Surface* background, Player* player) {
    SDL_Rect bgRect = {player->bgX, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Rect playerRect = {player->x, player->y, PLAYER_WIDTH, PLAYER_HEIGHT};

    printf("Player X: %d, Player Y: %d, Background X: %d\n", player->x, player->y, player->bgX);

    SDL_BlitSurface(background, NULL, screen, &bgRect);  // Draw background
    if (player->sprite) {
        SDL_BlitSurface(player->sprite, NULL, screen, &playerRect);  // Draw player
    } else {
        printf("⚠ Player sprite is NULL!\n");
    }
    SDL_Flip(screen);
}



// Handle input
int handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) return 0;

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_d) {
                player.dx = SPEED;
                player.facingRight = 1;
                player.sprite = Run_R;  // Use running sprite
            }
            if (event.key.keysym.sym == SDLK_q) {
                player.dx = -SPEED;
                player.facingRight = 0;
                player.sprite = Run_L;  // Use running sprite
            }
            if (event.key.keysym.sym == SDLK_z && !player.isJumping) {
                player.dy = -JUMP_FORCE;
                player.isJumping = 1;
            }
        }
        
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_q) {
                player.dx = 0;
                player.sprite = player.facingRight ? Idle_R : Idle_L;  // Return to idle sprite
            }
        }
        
    }
    return 1;
}

// Main function
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_SWSURFACE);
    if (!screen) {
        printf("Failed to set video mode: %s\n", SDL_GetError());
        return 1;
    }
    player.sprite = Idle_R;  // Default sprite when not moving
    player.bgX = 0;
    player.x = 100;
    player.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
    player.dx = 0;
    player.dy = 0;
    player.isJumping = 0;
    player.facingRight = 1;
    player.isRunning = 0;

    run_background();
    run_playerSTANDING();
    run_playerRUNNING();

    int running = 1;
    while (running) {
        running = handle_events();
        update(&player, &player.bgX);  // Pass player and background X offset
        render(screen, background, &player);  // Pass screen, background, and player
        SDL_Delay(16);  // Limit FPS
    }
    

    SDL_FreeSurface(Idle_R);
    SDL_FreeSurface(Idle_L);
    SDL_FreeSurface(Run_R);
    SDL_FreeSurface(Run_L);
    SDL_FreeSurface(background);
    SDL_Quit();

    return 0;
}