#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include "enigme.h"
#include <time.h> 

enigme Decomposer(char *ch) {
    enigme e;
    int i = 0, Taille;
    char sc[200];

    while (ch[i] != '?' && ch[i] != '\0') {
        sc[i] = ch[i];
        i++;
    }
    sc[i++] = '?';
    sc[i] = '\0';
    strcpy(e.question, sc);

    Taille = i;
    while (ch[i] != '.' && ch[i] != '\0') sc[i - Taille] = ch[i++];
    sc[i - Taille] = '\0';
    strcpy(e.r1, sc);

    i++; Taille = i;
    while (ch[i] != '.' && ch[i] != '\0') sc[i - Taille] = ch[i++];
    sc[i - Taille] = '\0';
    strcpy(e.r2, sc);

    i++; Taille = i;
    while (ch[i] != '.' && ch[i] != '\0') sc[i - Taille] = ch[i++];
    sc[i - Taille] = '\0';
    strcpy(e.r3, sc);

    e.bonne = ch[strlen(ch) - 2];
    if (e.bonne < '1' || e.bonne > '3') {
    e.bonne = ch[strlen(ch) - 3];
}
e.bonne -= '0';

    return e;
}

void Init_Enigme(enigme *e) {
    e->font = TTF_OpenFont("/home/gmati/Enigme (7th copy)/pixel .ttf", 30);
    if (!e->font) {
        printf("Erreur chargement police : %s\n", TTF_GetError());
        exit(1);
    }

    e->textColor = (SDL_Color){0, 0, 0};

    e->surface_question = TTF_RenderText_Solid(e->font, e->question, e->textColor);
    e->surface_rep1 = TTF_RenderText_Solid(e->font, e->r1, e->textColor);
    e->surface_rep2 = TTF_RenderText_Solid(e->font, e->r2, e->textColor);
    e->surface_rep3 = TTF_RenderText_Solid(e->font, e->r3, e->textColor);

    e->pos_question = (SDL_Rect){50, 220};
    e->pos_rep1 = (SDL_Rect){160, 350};
    e->pos_rep2 = (SDL_Rect){160, 450};
    e->pos_rep3 = (SDL_Rect){160, 550};

    e->tempsPrecedent = SDL_GetTicks();
    e->compteur = 20;
    e->positionTemps = (SDL_Rect){520, 60};
}


void Afficherenigme(enigme *e, SDL_Surface *screen) {
    SDL_BlitSurface(e->surface_question, NULL, screen, &e->pos_question);
    SDL_BlitSurface(e->surface_rep1, NULL, screen, &e->pos_rep1);
    SDL_BlitSurface(e->surface_rep2, NULL, screen, &e->pos_rep2);
    SDL_BlitSurface(e->surface_rep3, NULL, screen, &e->pos_rep3);
}

void afficher_message_succes(SDL_Surface *screen, Mix_Chunk *win) {
    TTF_Font *font = TTF_OpenFont("/home/gmati/Enigme (7th copy)/pixel .ttf", 40);
    SDL_Surface *msg = TTF_RenderText_Solid(font, "PASS!", (SDL_Color){0,0, 255});
    SDL_Rect pos = {250, 700};
    SDL_BlitSurface(msg, NULL, screen, &pos);
    Mix_PlayChannel(-1, win, 0);
    SDL_FreeSurface(msg);
    TTF_CloseFont(font);
}

void afficher_message_echec(SDL_Surface *screen, Mix_Chunk *lose) {
    TTF_Font *font = TTF_OpenFont("/home/gmati/Enigme (7th copy)/pixel .ttf", 40);
    SDL_Surface *msg = TTF_RenderText_Solid(font, "FAUX!", (SDL_Color){255, 0, 0});
    SDL_Rect pos = {250, 700};
    SDL_BlitSurface(msg, NULL, screen, &pos);
    Mix_PlayChannel(-1, lose, 0);
    SDL_FreeSurface(msg);
    TTF_CloseFont(font);
}


enigme generer(char *nom_fichier) {
    FILE *f = fopen(nom_fichier, "r");
    if (!f) {
        printf("Erreur ouverture fichier : %s\n", nom_fichier);
        exit(1);
    }

    char *lignes[MAX_QUESTIONS];
    char buffer[256];
    int n = 0;

    while (fgets(buffer, sizeof(buffer), f) && n < MAX_QUESTIONS) {
        lignes[n] = strdup(buffer);
        n++;
    }
    fclose(f);

    if (n == 0) {
        printf("Aucune énigme trouvée dans le fichier.\n");
        exit(1);
    }

    srand(time(NULL));
    int idx = rand() % n;

    enigme e = Decomposer(lignes[idx]);
    Init_Enigme(&e);  

    for (int i = 0; i < n; i++) free(lignes[i]);

    return e;
}

int resolution_enigme(SDL_Surface *screen, SDL_Surface *background, enigme *e, int *niveau, int *score, int *vie, Mix_Chunk *win, Mix_Chunk *lose) {
 
    SDL_Event ev;
    int rep = -1;
    Uint32 start = SDL_GetTicks();
    Uint32 elapsed = 0;

    // Boucle pour gérer la réponse de l'utilisateur pendant 15 secondes
    while (rep == -1 && elapsed < 15000) {
        SDL_BlitSurface(background, NULL, screen, NULL);
        Afficherenigme(e, screen);
        afficher_timer(screen, e);
        SDL_Flip(screen);

        // Boucle pour détecter les événements de la souris
        while (SDL_PollEvent(&ev)) {
            if (ev.type == SDL_QUIT) exit(0); // Quitter si l'utilisateur ferme la fenêtre
            if (ev.type == SDL_MOUSEBUTTONDOWN) {
                int x = ev.button.x;
                int y = ev.button.y;

                // Vérification de la réponse
                if (y >= e->pos_rep1.y && y <= e->pos_rep1.y + 40) rep = 1;
                else if (y >= e->pos_rep2.y && y <= e->pos_rep2.y + 40) rep = 2;
                else if (y >= e->pos_rep3.y && y <= e->pos_rep3.y + 40) rep = 3;
            }
        }

        elapsed = SDL_GetTicks() - start;
    }

if (rep == e->bonne) {
    *score += 10;
    *vie += 1;
    *niveau += 1;
    afficher_message_succes(screen, win);
    SDL_Flip(screen);
    SDL_Delay(4000);
    return 1; // ✅ bonne réponse, on veut quitter
} else {
    *score -= 5;
    if (*score <= 0) *vie = 0;
    afficher_message_echec(screen, lose);
    SDL_Flip(screen);
    SDL_Delay(4000);
    return 0; // ❌ mauvaise réponse, on peut continuer
}


    SDL_Delay(4000); 
}

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
        e->compteur--;
    }

    if (e->compteur > 0)
        SDL_BlitSurface(animations[e->compteur % 4], NULL, screen, &e->positionTemps);

    for (int i = 0; i < 4; i++) SDL_FreeSurface(animations[i]);
}

void Libererenigme(enigme *e) {
    SDL_FreeSurface(e->surface_question);
    SDL_FreeSurface(e->surface_rep1);
    SDL_FreeSurface(e->surface_rep2);
    SDL_FreeSurface(e->surface_rep3);
    TTF_CloseFont(e->font);
}

