#include "best_score.h"
#include "../menu.h"
#include "utilities.h"
#include <stdio.h>

void init_best_score(Menu *m) {
    // Load background
    m->bg_meilleur = IMG_Load("/home/T.rebirth/menu/assets/images/5.jpg");
    if(!m->bg_meilleur) {
        printf("Error loading best score background: %s\n", IMG_GetError());
    }

    // Load input field textures
    m->espace_saisie[0] = IMG_Load("/home/T.rebirth/menu/assets/images/saisir.jpg");
    m->espace_saisie[1] = IMG_Load("/home/T.rebirth/menu/assets/images/zone.jpg");
    
    // Load star icons
    m->etoile[0] = IMG_Load("/home/T.rebirth/menu/assets/images/kalb.png");
    m->etoile[1] = IMG_Load("/home/T.rebirth/menu/assets/images/kalb.png");
    m->etoile[2] = IMG_Load("/home/T.rebirth/menu/assets/images/kalb.png");

    // Create text surfaces
    m->textNom = TTF_RenderText_Blended(m->arial, "USER NAME", m->textColor);
    m->textMeilleur = TTF_RenderText_Blended(m->arial, "BEST SCORE", m->textColor);

    // Position input field
    m->pos_espace_saisie = (SDL_Rect){
        830, 524, 
        m->espace_saisie[0]->w, 
        m->espace_saisie[0]->h
    };

    // Position stars
    m->pos_etoile[0] = (SDL_Rect){342, 276, m->etoile[0]->w, m->etoile[0]->h};
    m->pos_etoile[1] = (SDL_Rect){342, 495, m->etoile[1]->w, m->etoile[1]->h};
    m->pos_etoile[2] = (SDL_Rect){342, 703, m->etoile[2]->w, m->etoile[2]->h};

    // Position text elements
    m->pos_meilleur = (SDL_Rect){
        (1920/2 - m->textMeilleur->w/2),
        130,
        m->textMeilleur->w,
        m->textMeilleur->h
    };
    
    m->pos_nom = (SDL_Rect){
        (1920/2 - m->textNom->w/2),
        429,
        m->textNom->w,
        m->textNom->h
    };
}

void afficher_best_score(Menu m, SDL_Surface *ecran) {
    // Draw background
    SDL_BlitSurface(m.bg_meilleur, NULL, ecran, NULL);

    // Draw title
    SDL_BlitSurface(m.textMeilleur, NULL, ecran, &m.pos_meilleur);
    
    // Draw username label
    SDL_BlitSurface(m.textNom, NULL, ecran, &m.pos_nom);

    // Draw input field (active/hover state)
    SDL_BlitSurface(
        m.espace_saisie[(m.etat_espace_saisie || m.espace_saisie_actif)], 
        NULL, 
        ecran, 
        &m.pos_espace_saisie
    );

    // Draw stars
    SDL_BlitSurface(m.etoile[0], NULL, ecran, &m.pos_etoile[0]);
    SDL_BlitSurface(m.etoile[1], NULL, ecran, &m.pos_etoile[1]);
    SDL_BlitSurface(m.etoile[2], NULL, ecran, &m.pos_etoile[2]);
}

void miseajour_best_score(Menu *m) {
    // Update input field hover state
    m->etat_espace_saisie = collision_avec_souris(m->pos_espace_saisie);
}