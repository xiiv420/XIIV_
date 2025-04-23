#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"

int main() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("Erreur TTF_Init: %s\n", TTF_GetError());
        return 1;
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) == -1) {
        printf("Erreur Mix_OpenAudio: %s\n", Mix_GetError());
        return 1;
    }

    SDL_Surface *screen = SDL_SetVideoMode(680, 840, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (!screen) {
        printf("Erreur SetVideoMode: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Surface *background = IMG_Load("backround.png");
    if (!background) {
        printf("Erreur chargement background: %s\n", IMG_GetError());
        return 1;
    }

    Mix_Music *music = Mix_LoadMUS("son.mp3");
    Mix_Chunk *win = Mix_LoadWAV("win.wav");
    Mix_Chunk *lose = Mix_LoadWAV("fail.wav");

    if (!music || !win || !lose) {
        printf("Erreur chargement sons\n");
        return 1;
    }

    Mix_PlayMusic(music, -1);

    int niveau = 1, score = 0, vie = 3;

while (vie > 0 && niveau <= 3) {
    enigme e = generer("enigmes.txt");

    int result = resolution_enigme(screen, background, &e, &niveau, &score, &vie, win, lose);
    Libererenigme(&e);

    if (result == 1) break; // ✅ Arrêter le jeu après bonne réponse
}


    Mix_FreeChunk(win);
    Mix_FreeChunk(lose);
    Mix_FreeMusic(music);
    SDL_FreeSurface(background);

    TTF_Quit();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}

