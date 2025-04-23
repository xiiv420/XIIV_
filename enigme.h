#ifndef ENIGME_H
#define ENIGME_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define MAX_QUESTIONS 100

typedef struct {
    char question[100];
    char r1[50], r2[50], r3[50];
    int numQuestSelect;
    int bonne;

    SDL_Surface *surface_question;
    SDL_Surface *surface_rep1;
    SDL_Surface *surface_rep2;
    SDL_Surface *surface_rep3;

    SDL_Rect pos_question;
    SDL_Rect pos_rep1;
    SDL_Rect pos_rep2;
    SDL_Rect pos_rep3;

    TTF_Font *font;
    SDL_Color textColor;

    int tempsActuel, tempsPrecedent, compteur;
    SDL_Surface *afficherTemps;
    SDL_Rect positionTemps;
    
    int etat_enigme;
} enigme;

void Init_Enigme(enigme *e);
void Afficherenigme(enigme *e, SDL_Surface *screen);
void afficher_message_succes(SDL_Surface *screen, Mix_Chunk *win);
void afficher_message_echec(SDL_Surface *screen, Mix_Chunk *lose);

enigme generer(char *nom_du_fichier);

int resolution_enigme(SDL_Surface *screen, SDL_Surface *background, enigme *e, int *niveau, int *score, int *vie, Mix_Chunk *win, Mix_Chunk *lose);

void afficher_timer(SDL_Surface *screen,enigme *e);

void Libererenigme(enigme *e);


#endif

