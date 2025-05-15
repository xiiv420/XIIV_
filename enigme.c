
/**
* @file enigme.c
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
#include <time.h>
#include <SDL/SDL_rotozoom.h> 

/**
* @brief Découpe une chaîne représentant une ligne d'énigme en question, réponses et bonne réponse.
* @param ch La ligne à analyser.
* @return Une structure enigme remplie.
*/

enigme Decomposer(char *ch) {
    enigme e;
    int i = 0, j = 0;
    char sc[200];


    while (ch[i] != '?' && ch[i] != '\0') {
        sc[j++] = ch[i++];
    }
    sc[j++] = '?';
    sc[j] = '\0';
    strcpy(e.question, sc);

    j = 0;
    i++;
    while (ch[i] != '.' && ch[i] != '\0') {
        sc[j++] = ch[i++];
    }
    sc[j] = '\0';
    strcpy(e.r1, sc);

    j = 0;
    i++;
    while (ch[i] != '.' && ch[i] != '\0') {
        sc[j++] = ch[i++];
    }
    sc[j] = '\0';
    strcpy(e.r2, sc);

    j = 0;
    i++;
    while (ch[i] != '.' && ch[i] != '\0') {
        sc[j++] = ch[i++];
    }
    sc[j] = '\0';
    strcpy(e.r3, sc);

    e.bonne = ch[strlen(ch) - 2] - '0';

    return e;
}

/**
* @brief Initialise les surfaces et les positions d'affichage de l'énigme.
* @param e Pointeur vers la structure enigme à initialiser.
* @return Rien.
*/

void Init_Enigme(enigme *e) {
    e->font = TTF_OpenFont("/home/gmati/Enigme (7th copy)/pixel .ttf", 33);
    if (!e->font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        exit(1);
    }

    e->textColor = (SDL_Color){255, 255, 255};

    e->surface_question = TTF_RenderText_Solid(e->font, e->question, e->textColor);
    e->surface_rep1 = TTF_RenderText_Solid(e->font, e->r1, e->textColor);
    e->surface_rep2 = TTF_RenderText_Solid(e->font, e->r2, e->textColor);
    e->surface_rep3 = TTF_RenderText_Solid(e->font, e->r3, e->textColor);

    e->pos_question = (SDL_Rect){250, 220};
    e->pos_rep1 = (SDL_Rect){450, 380};
    e->pos_rep2 = (SDL_Rect){450, 480};
    e->pos_rep3 = (SDL_Rect){450, 580};

    e->tempsPrecedent = SDL_GetTicks();
    e->compteur = 20;
    e->positionTemps = (SDL_Rect){1120, 70};
}

/**
* @brief Affiche l'énigme (question + réponses) sur l'écran.
* @param e Pointeur vers la structure enigme à afficher.
* @param screen La surface de l'écran sur laquelle dessiner.
* @return Rien.
*/

void Afficherenigme(enigme *e, SDL_Surface *screen) {
    SDL_BlitSurface(e->surface_question, NULL, screen, &e->pos_question);
    SDL_BlitSurface(e->surface_rep1, NULL, screen, &e->pos_rep1);
    SDL_BlitSurface(e->surface_rep2, NULL, screen, &e->pos_rep2);
    SDL_BlitSurface(e->surface_rep3, NULL, screen, &e->pos_rep3);
}

/**
* @brief Génère une énigme aléatoire à partir d’un fichier texte.
* @param nom_fichier Le nom du fichier contenant les énigmes.
* @return Une structure enigme initialisée.
*/

enigme generer(char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        printf("Erreur ouverture fichier : %s\n", nom_fichier);
        exit(1);
    }

    char *lignes[MAX_QUESTIONS];
    char ligne_temp[256];
    int n = 0;

    while (fgets(ligne_temp, sizeof(ligne_temp), f) && n < MAX_QUESTIONS) {
        lignes[n] = malloc(strlen(ligne_temp) + 1);
        if (lignes[n] != NULL) {
            strcpy(lignes[n], ligne_temp);
            n++;
        }
    }
    fclose(f);

    srand(time(NULL));
    static int deja_pose[MAX_QUESTIONS] = {0};
    int idx;

    do {
        idx = rand() % n;  
    } while (deja_pose[idx]); 
 
    deja_pose[idx] = 1;

    enigme e = Decomposer(lignes[idx]);
    Init_Enigme(&e);
    for (int i = 0; i < n; i++) {
        free(lignes[i]);
    }
   
   return e;
}

/**
* @brief Gère la résolution d'une énigme avec score, sons, clics souris et clavier.
* @param screen Surface de l'écran.
* @param background Image de fond.
* @param e Pointeur vers l’énigme à résoudre.
* @param score Pointeur vers le score du joueur à modifier.
* @param win Son de victoire.
* @param lose Son d’échec.
* @param clickSound Son du clic.
* @return 1 si la bonne réponse a été donnée, 0 sinon.
*/

int resolution_enigme(SDL_Surface *screen, SDL_Surface *background, enigme *e, int *score, Mix_Chunk *win, Mix_Chunk *lose, Mix_Chunk *clickSound) {
    SDL_Event event;
    int rep = -1;
    int running = 1;
    Uint32 start = SDL_GetTicks();
    Uint32 elapsed = 0;

    while (rep == -1 && elapsed < 15000 && running) {
        SDL_BlitSurface(background, NULL, screen, NULL);
        Afficherenigme(e, screen);
        afficher_timer(screen, e);
        SDL_Flip(screen);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    exit(0);
                    break;

                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = 0;
                    }
                    else if (event.key.keysym.sym == SDLK_a) {
                        rep = 1;
                        if (clickSound) Mix_PlayChannel(-1, clickSound, 0);
                    }
                    else if (event.key.keysym.sym == SDLK_b) {
                        rep = 2;
                        if (clickSound) Mix_PlayChannel(-1, clickSound, 0);
                    }
                    else if (event.key.keysym.sym == SDLK_c) {
                        rep = 3;
                        if (clickSound) Mix_PlayChannel(-1, clickSound, 0);
                    }

                    if (rep != -1)
                        running = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        int x = event.button.x;
                        int y = event.button.y;

                        if (clickSound) Mix_PlayChannel(-1, clickSound, 0);

                        if (y >= e->pos_rep1.y && y <= e->pos_rep1.y + 40)
                            rep = 1;
                        else if (y >= e->pos_rep2.y && y <= e->pos_rep2.y + 40)
                            rep = 2;
                        else if (y >= e->pos_rep3.y && y <= e->pos_rep3.y + 40)
                            rep = 3;

                        if (rep != -1)
                            running = 0;
                    }
                    break;
            }
        }

        elapsed = SDL_GetTicks() - start;
    }

    // gestion d score
    if (rep == e->bonne) {
        *score += 10;
        afficher_message(screen, background, "PASS!", (SDL_Color){0, 0, 255}, win);
        SDL_Delay(4000);
        return 1;
    } else {
        *score -= 5;
        if (*score <= 0) ;
        afficher_message(screen, background, "FAUX!", (SDL_Color){255, 0, 0}, lose);
        SDL_Delay(3000);
        return 0;
    }
}

/**
* @brief Affiche une animation de minuterie dégressive.
* @param screen La surface sur laquelle dessiner.
* @param e Pointeur vers la structure enigme pour suivre le temps.
* @return Rien.
*/

void afficher_timer(SDL_Surface *screen, enigme *e) {
    SDL_Surface *animations[4] = {
        IMG_Load("/home/gmati/Enigme (7th copy)/animation1.png"),
        IMG_Load("/home/gmati/Enigme (7th copy)/animation2.png"),
        IMG_Load("/home/gmati/Enigme (7th copy)/animation3.png"),
        IMG_Load("/home/gmati/Enigme (7th copy)/animation4.png")
    };
    
    for (int i = 0; i < 4; i++) {
        if (!animations[i]) {
            fprintf(stderr, "Erreur chargement animation : %s\n", IMG_GetError());
            return;
        }
    }

    Uint32 maintenant = SDL_GetTicks();
    if (maintenant - e->tempsPrecedent >= 1000) { 
        e->tempsPrecedent = maintenant;
        if (e->compteur > 0) {
            e->compteur--;
        }
    }

    if (e->compteur > 0) {
        SDL_BlitSurface(animations[e->compteur % 4], NULL, screen, &e->positionTemps);
    }

    for (int i = 0; i < 4; i++) {
        SDL_FreeSurface(animations[i]);
    }
}

/**
 * @brief Affiche un message animé sur l'écran avec effet de zoom et rotation, accompagné d'un son.
 *
 * Cette fonction affiche un texte sur l'écran principal en effectuant une animation
 * de zoom et rotation pendant une durée déterminée. Le fond de l'écran est reblitté
 * à chaque image pour conserver l’arrière-plan initial.
 *
 * @param screen La surface de l’écran principal où le message est affiché.
 * @param background La surface représentant le fond à réafficher à chaque frame pour ne pas effacer l’arrière-plan.
 * @param texte_a_afficher Le message à afficher sous forme de chaîne de caractères.
 * @param couleur La couleur du texte affiché (de type SDL_Color).
 * @param sound Le son à jouer en même temps que l’animation du message (de type Mix_Chunk*).
 *
 * @return Cette fonction ne retourne rien (void).
 */

void afficher_message(SDL_Surface *screen, SDL_Surface *background, char* texte_a_afficher, SDL_Color couleur, Mix_Chunk *sound) {
    TTF_Font *font = NULL;
    SDL_Surface *msg = NULL;
    SDL_Surface *zoomed = NULL;
    SDL_Rect pos;
    int frames = 60;
    int i;
    float progress;
    float zoom;
    float rotation;
    font = TTF_OpenFont("/home/gmati/Enigme (7th copy)/pixel .ttf", 40);
    if (!font) {
        printf("Erreur ouverture police: %s\n", TTF_GetError());
        return;
    }
    msg = TTF_RenderText_Solid(font, texte_a_afficher, couleur);
    if (!msg) {
        printf("Erreur rendu texte: %s\n", TTF_GetError());
        TTF_CloseFont(font);
        return;
    }
    Mix_PlayChannel(-1, sound, 0);
//
    for (i = 0; i <= frames; i++) {
        progress = (float)i / frames;
        zoom = 0.5 + progress * (1.5 - 0.5);
        rotation = progress * 360.0;

        zoomed = rotozoomSurface(msg,rotation, zoom, 0);

        if (!zoomed) {
            printf("Erreur lors de l'application de rotozoom.\n");
            break;
        }
//
        pos.x = (screen->w - zoomed->w) / 2;
        pos.y = (screen->h - zoomed->h) / 2;

        SDL_BlitSurface(background, NULL, screen, NULL);
        SDL_BlitSurface(zoomed, NULL, screen, &pos);
        SDL_Flip(screen);

        SDL_FreeSurface(zoomed);
        SDL_Delay(30);
    }
    SDL_FreeSurface(msg);
    TTF_CloseFont(font);
}

/**
* @brief Libère les surfaces et ressources associées à une énigme.
* @param e Pointeur vers l’énigme à libérer.
* @return Rien.
*/

void Libererenigme(enigme *e) {
    SDL_FreeSurface(e->surface_question);
    SDL_FreeSurface(e->surface_rep1);
    SDL_FreeSurface(e->surface_rep2);
    SDL_FreeSurface(e->surface_rep3);
    TTF_CloseFont(e->font);
}

