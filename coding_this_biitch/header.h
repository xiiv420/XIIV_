#ifndef HEADER_H
#define HEADER_H

#include "SDL/SDL.h"

// CONSTANTS
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define LEFT_LIMIT 200
#define RIGHT_LIMIT 700
#define JUMP_STRENGTH 15
#define GRAVITY 1
#define PLAYER_SPEED 7
#define MONSTER_SPEED 2
#define MONSTER_SLOW_SPEED 0.2

// STRUCTS
typedef struct {
    int x, y;
    int velocityY;
    int isJumping;
    int onGround;
    int health;
    SDL_Surface *sprite;
} Player;

typedef struct {
    SDL_Rect pos;
    int speed;
    int attackCooldown;
    SDL_Surface *sprite;
} Enemy;

typedef struct {
    SDL_Surface *background;
    int bgX;
} Background;

// FUNCTION PROTOTYPES
void init_player(Player *player, int startX, int startY);
void move_player(Player *player, const Uint8 *keystate);
void start_jump(Player *player);
void update_jump(Player *player);
void handle_input(int *running, Player *player);
void initEnemy(Enemy *e, int x, int y);
void moveEnemy(Enemy *e, int player_x, int backgroundMoving);
void attackPlayer(Enemy *e, Player *player);
void drawEnemy(Enemy *e, SDL_Surface *screen);
void drawHealthBar(Player *player, SDL_Surface *screen);
void drawGameOver(SDL_Surface *screen, int *running);
void resetGame(Player *player, Enemy *monster, Background *bg);
void update_background(Background *bg, int *backgroundMoving, Player *player, Enemy *monster);

#endif
