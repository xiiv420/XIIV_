#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <SDL/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_WIDTH 128
#define PLAYER_HEIGHT 128
#define SPEED 5
#define JUMP_FORCE 15
#define GRAVITY 1

#define FRAME_WIDTH 128
#define FRAME_HEIGHT 128
#define FRAME_COUNT 10

extern SDL_Surface* screen;
extern SDL_Surface* background;
extern SDL_Surface* Idle_R;
extern SDL_Surface* Idle_L;
extern SDL_Surface* Run_R;
extern SDL_Surface* Run_L;

typedef struct {
    int x, y;
    int dx, dy;
    int isJumping;
    int facingRight;
    int isRunning;
    SDL_Surface* sprite;
} Player;

extern Player player;

void run_background();
void run_playerSTANDING();
void run_playerRUNNING();
void update();
void render();
int handle_events();

#endif
