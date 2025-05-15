
/**
* @file main.c
* @brief Gestion des énigmes du jeu.
* @author C Team
* @version 0.1
* @date Apr 01, 2015
*
* Implémentation des énigmes, avec gestion des scores, du chronomètre et de la progression des niveaux.
*
*/

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

    SDL_Surface *screen = SDL_SetVideoMode(1338, 850, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
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
    if (!music) {
        printf("Erreur chargement musique : %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(music, -1);
    }
      
    Mix_Chunk *clickSound = Mix_LoadWAV("/home/gmati/Enigme (7th copy)/bref.wav");
    if (!clickSound) {
        printf("Erreur chargement son bouton : %s\n", Mix_GetError());
        return 1;
    }
   
    Mix_Chunk *win = Mix_LoadWAV("win.wav");
    Mix_Chunk *lose = Mix_LoadWAV("fail.wav");

    if ( !win || !lose) {
        printf("Erreur chargement sons\n");
        return 1;
    }
    Mix_PlayMusic(music, -1);

    int score = 0;
    int etat_enigme=0; 
    int level = 1;     
    int level_fini = 1; // Initialisation, le niveau est terminé au départ

   while (level_fini) // On entre dans la boucle **une fois que le niveau est terminé**
    {
    enigme e = generer("enigmes.txt");
    int resultat = resolution_enigme(screen, background, &e, &score, win, lose, clickSound); 
    Libererenigme(&e); 

    if (resultat == 1) 
    {
        printf("Bravo, énigme réussie !\n"); 
        etat_enigme = 1;
        level++; 
        printf("Passage au niveau suivant %d...\n", level);
        level_fini = 0; // On sort de la boucle du niveau actuel
    }
    else if (resultat == -1) 
    {
        printf("Mauvaise réponse, réessaie une nouvelle énigme...\n");
        etat_enigme = -1; 
        
    }

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

