#include "player_menu.h"
#include "../menu.h"
#include "utilities.h"
#include <stdio.h>

void init_player_menu(Menu *m) {
    // Load background
    m->bg_joueur = IMG_Load("/home/T.rebirth/menu/assets/images/4.jpg");
    if(!m->bg_joueur) {
        printf("Error loading player menu background: %s\n", IMG_GetError());
    }

    // Load player type buttons
    m->btn_mono[0] = IMG_Load("/home/T.rebirth/menu/assets/images/single.png");
    m->btn_mono[1] = IMG_Load("/home/T.rebirth/menu/assets/images/singler.png");
    m->btn_multi[0] = IMG_Load("/home/T.rebirth/menu/assets/images/multin.png");
    m->btn_multi[1] = IMG_Load("/home/T.rebirth/menu/assets/images/multir.png");

    // Load avatar buttons
    m->btn_avatar1[0] = IMG_Load("/home/T.rebirth/menu/assets/images/1.png");
    m->btn_avatar1[1] = IMG_Load("/home/T.rebirth/menu/assets/images/1.png"); // Assuming same image for both states
    m->btn_avatar2[0] = IMG_Load("/home/T.rebirth/menu/assets/images/2.png");
    m->btn_avatar2[1] = IMG_Load("/home/T.rebirth/menu/assets/images/2.png");

    // Load input method buttons
    m->btn_input1[0] = IMG_Load("/home/T.rebirth/menu/assets/images/flechb.png");
    m->btn_input1[1] = IMG_Load("/home/T.rebirth/menu/assets/images/gr.png");
    m->btn_input2[0] = IMG_Load("/home/T.rebirth/menu/assets/images/dr.png");
    m->btn_input2[1] = IMG_Load("/home/T.rebirth/menu/assets/images/drr.png");

    // Load navigation buttons
    m->btn_retour[0] = IMG_Load("/home/T.rebirth/menu/assets/images/back.png");
    m->btn_retour[1] = IMG_Load("/home/T.rebirth/menu/assets/images/backr.png");
    m->btn_valider[0] = IMG_Load("/home/T.rebirth/menu/assets/images/nextn.png");
    m->btn_valider[1] = IMG_Load("/home/T.rebirth/menu/assets/images/next.png");

    // Set button positions
    m->pos_btn_mono = (SDL_Rect){592, 539, m->btn_mono[0]->w, m->btn_mono[0]->h};
    m->pos_btn_multi = (SDL_Rect){1055, 539, m->btn_multi[0]->w, m->btn_multi[0]->h};
    m->pos_btn_avatar1 = (SDL_Rect){533, 190, m->btn_avatar1[0]->w, m->btn_avatar1[0]->h};
    m->pos_btn_avatar2 = (SDL_Rect){1000, 190, m->btn_avatar2[0]->w, m->btn_avatar2[0]->h};
    m->pos_btn_input1 = (SDL_Rect){533, 390, m->btn_input1[0]->w, m->btn_input1[0]->h};
    m->pos_btn_input2 = (SDL_Rect){1293, 390, m->btn_input2[0]->w, m->btn_input2[0]->h};
    m->pos_btn_retour = (SDL_Rect){1384, 756, m->btn_retour[0]->w, m->btn_retour[0]->h};
    m->pos_btn_valider = (SDL_Rect){936, 643, m->btn_valider[0]->w, m->btn_valider[0]->h};
}

void afficher_player_menu(Menu m, SDL_Surface *ecran) {
    SDL_BlitSurface(m.bg_joueur, NULL, ecran, NULL);

    if(m.num_page_joueur == 0) {
        // Player type selection page
        SDL_BlitSurface(m.btn_mono[m.etat_btn_mono], NULL, ecran, &m.pos_btn_mono);
        SDL_BlitSurface(m.btn_multi[m.etat_btn_multi], NULL, ecran, &m.pos_btn_multi);
    } else {
        // Avatar and input selection page
        SDL_BlitSurface(m.btn_avatar1[m.etat_btn_avatar1], NULL, ecran, &m.pos_btn_avatar1);
        SDL_BlitSurface(m.btn_avatar2[m.etat_btn_avatar2], NULL, ecran, &m.pos_btn_avatar2);
        SDL_BlitSurface(m.btn_input1[m.etat_btn_input1], NULL, ecran, &m.pos_btn_input1);
        SDL_BlitSurface(m.btn_input2[m.etat_btn_input2], NULL, ecran, &m.pos_btn_input2);
    }

    // Always show navigation buttons
    SDL_BlitSurface(m.btn_retour[m.etat_btn_retour], NULL, ecran, &m.pos_btn_retour);
    SDL_BlitSurface(m.btn_valider[m.etat_btn_valider], NULL, ecran, &m.pos_btn_valider);
}

void miseajour_player_menu(Menu *m) {
    // Update back button state
    m->etat_btn_retour = collision_avec_souris(m->pos_btn_retour);

    if(m->num_page_joueur == 0) {
        // Player type selection page
        m->etat_btn_mono = collision_avec_souris(m->pos_btn_mono);
        m->etat_btn_multi = collision_avec_souris(m->pos_btn_multi);
    } else {
        // Avatar and input selection page
        m->etat_btn_avatar1 = collision_avec_souris(m->pos_btn_avatar1);
        m->etat_btn_avatar2 = collision_avec_souris(m->pos_btn_avatar2);
        m->etat_btn_input1 = collision_avec_souris(m->pos_btn_input1);
        m->etat_btn_input2 = collision_avec_souris(m->pos_btn_input2);
        m->etat_btn_valider = collision_avec_souris(m->pos_btn_valider);
    }
}