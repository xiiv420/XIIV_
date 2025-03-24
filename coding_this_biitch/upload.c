#include "header.h"
#include <stdio.h>
#include <SDL/SDL.h>

SDL_Surface *idle = NULL;
SDL_Surface *monster = NULL;
SDL_Surface *background_1 = NULL;
SDL_Surface *background_2 = NULL;
SDL_Surface *background_3 = NULL;
SDL_Surface *run[10] = {NULL};  // Store all running frames
SDL_Surface *jump[10] = {NULL}; // Store all jumping frames

void load_player() {
    idle = SDL_LoadBMP("/home/BROO/Idle.bmp");
    if (!idle) {
        printf("Failed to load Idle.bmp: %s\n", SDL_GetError());
    }
}

void load_monster() {
    monster = SDL_LoadBMP("/home/BROO/monster.bmp");
    if (!monster) {
        printf("Failed to load monster.bmp: %s\n", SDL_GetError());
    }
}

void load_background_1() {
    background_1 = SDL_LoadBMP("/home/BROO/background_1.bmp");
    if (!background_1) {
        printf("Failed to load background_1.bmp: %s\n", SDL_GetError());
    }
}

void load_background_2() {
    background_2 = SDL_LoadBMP("/home/BROO/background_2.bmp");
    if (!background_2) {
        printf("Failed to load background_2.bmp: %s\n", SDL_GetError());
    }
}

void load_background_3() {
    background_3 = SDL_LoadBMP("/home/BROO/background_3.bmp");
    if (!background_3) {
        printf("Failed to load background_3.bmp: %s\n", SDL_GetError());
    }
}

void load_player_run() {
    char *player_run_files[10] = {
        "/home/BROO/run1.bmp", "/home/BROO/run2.bmp", "/home/BROO/run3.bmp", "/home/BROO/run4.bmp", "/home/BROO/run5.bmp",
        "/home/BROO/run6.bmp", "/home/BROO/run7.bmp", "/home/BROO/run8.bmp", "/home/BROO/run9.bmp", "/home/BROO/run10.bmp"
    };

    for (int i = 0; i < num_player_run; i++) {
        run[i] = SDL_LoadBMP(player_run_files[i]);
        if (!run[i]) {
            printf("Failed to load %s: %s\n", player_run_files[i], SDL_GetError());
        }
    }
}

void load_player_jump() {
    char *player_jump_files[10] = {
        "/home/BROO/jump1.bmp", "/home/BROO/jump2.bmp", "/home/BROO/jump3.bmp", "/home/BROO/jump4.bmp", "/home/BROO/jump5.bmp",
        "/home/BROO/jump6.bmp", "/home/BROO/jump7.bmp", "/home/BROO/jump8.bmp", "/home/BROO/jump9.bmp", "/home/BROO/jump10.bmp"
    };

    for (int i = 0; i < num_player_jump; i++) {
        jump[i] = SDL_LoadBMP(player_jump_files[i]);
        if (!jump[i]) {
            printf("Failed to load %s: %s\n", player_jump_files[i], SDL_GetError());
        }
    }
}
