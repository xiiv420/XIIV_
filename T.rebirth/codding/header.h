#ifndef HEADER_H
#define HEADER_H

#include <SDL/SDL.h>
#include <stdio.h>
#include <stdlib.h>  // Needed for exit()

extern SDL_Surface *screen;  // Declare screen so all files can use it
extern int bg_x;             // Declare background x-offset


#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define JUMP_STRENGTH 20
#define GRAVITY 1

typedef struct {
    int x, y;
    int velocityY;
    int isJumping;
    int onGround;
    int speed;
} Player;

// Background functions
int initBackground();
void renderBackground(int bg_x);
void cleanupBackground();

// Player functions
void init_player(Player *player);
void move_player(Player *player, const Uint8 *keystate);
void update_player(Player *player);
void render_player(Player *player);

// Jumping functions
void start_jump(Player *player);
void update_jump(Player *player);

// Input handling
void handle_input(int *running, Player *player);

// Platform functions (NEW)
int getGroundHeight(int x);  // Function to get ground height at a given x position

//gameoverscreen 
int gameOverScreen(SDL_Surface *screen);


#endif
