#include "save_menu.h"
#include "../menu.h"
#include "utilities.h"
#include <stdio.h>

void init_save_menu(Menu *m) {
    // Load background
    m->bg_sauvegarde = IMG_Load("/home/T.rebirth/menu/assets/images/3.jpg");
    if(!m->bg_sauvegarde) {
        printf("Error loading save menu background: %s\n", IMG_GetError());
    }

    // Load button textures
    m->btn_oui[0] = IMG_Load("/home/T.rebirth/menu/assets/images/yesf.png");
    m->btn_oui[1] = IMG_Load("/home/T.rebirth/menu/assets/images/yesfr.png");
    m->btn_non[0] = IMG_Load("/home/T.rebirth/menu/assets/images/nof.png");
    m->btn_non[1] = IMG_Load("/home/T.rebirth/menu/assets/images/nofr.png");
    m->btn_charger[0] = IMG_Load("/home/T.rebirth/menu/assets/images/load.png");
    m->btn_charger[1] = IMG_Load("/home/T.rebirth/menu/assets/images/loadr.png");
    m->btn_nouvelle[0] = IMG_Load("/home/T.rebirth/menu/assets/images/new.png");
    m->btn_nouvelle[1] = IMG_Load("/home/T.rebirth/menu/assets/images/newr.png");

    // Set button positions
    m->pos_btn_oui = (SDL_Rect){716, 565, m->btn_oui[0]->w, m->btn_oui[0]->h};
    m->pos_btn_non = (SDL_Rect){1013, 565, m->btn_non[0]->w, m->btn_non[0]->h};
    m->pos_btn_charger = (SDL_Rect){970, 402, m->btn_charger[0]->w, m->btn_charger[0]->h};
    m->pos_btn_nouvelle = (SDL_Rect){970, 522, m->btn_nouvelle[0]->w, m->btn_nouvelle[0]->h};

    // Create save prompt text
    m->textSauvegarde = TTF_RenderText_Solid(m->arial, "DO YOU WANT TO SAVE YOUR GAME ?", m->textColor);
    m->PosTextSauv = (SDL_Rect){
        .x = (1920 / 2 - m->textSauvegarde->w / 2),
        .y = 500,
        .w = m->textSauvegarde ? m->textSauvegarde->w : 0,
        .h = m->textSauvegarde ? m->textSauvegarde->h : 0
    };
    
}

void afficher_save_menu(Menu *m, SDL_Surface *ecran) {
    if (!m || !ecran) {
        printf("Error: NULL menu or screen in afficher_save_menu\n");
        return;
    }

    if (!m->bg_sauvegarde) {
        printf("Error: bg_sauvegarde is NULL\n");
        return;
    }
    SDL_BlitSurface(m->bg_sauvegarde, NULL, ecran, NULL);

    if (m->num_page_sauv == 0) {
        if (m->textSauvegarde)
            SDL_BlitSurface(m->textSauvegarde, NULL, ecran, &m->PosTextSauv);
        if (m->btn_oui[m->etat_btn_oui])
            SDL_BlitSurface(m->btn_oui[m->etat_btn_oui], NULL, ecran, &m->pos_btn_oui);
        if (m->btn_non[m->etat_btn_non])
            SDL_BlitSurface(m->btn_non[m->etat_btn_non], NULL, ecran, &m->pos_btn_non);
    } else {
        if (m->btn_charger[m->etat_btn_charger])
            SDL_BlitSurface(m->btn_charger[m->etat_btn_charger], NULL, ecran, &m->pos_btn_charger);
        if (m->btn_nouvelle[m->etat_btn_nouvelle])
            SDL_BlitSurface(m->btn_nouvelle[m->etat_btn_nouvelle], NULL, ecran, &m->pos_btn_nouvelle);
    }
}




void miseajour_save_menu(Menu *m) {
    if(m->num_page_sauv == 0) {
        // Update yes/no button states
        m->etat_btn_oui = collision_avec_souris(m->pos_btn_oui);
        m->etat_btn_non = collision_avec_souris(m->pos_btn_non);
        
        // Play sound on state change
        if(m->etat_btn_oui && !m->etat_btn_oui_prev) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
        }
        if(m->etat_btn_non && !m->etat_btn_non_prev) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
        }
        m->etat_btn_oui_prev = m->etat_btn_oui;
        m->etat_btn_non_prev = m->etat_btn_non;
    } else {
        // Update load/new game states
        m->etat_btn_charger = collision_avec_souris(m->pos_btn_charger);
        m->etat_btn_nouvelle = collision_avec_souris(m->pos_btn_nouvelle);
        
        // Play sound on state change
        if(m->etat_btn_charger && !m->etat_btn_charger_prev) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
        }
        if(m->etat_btn_nouvelle && !m->etat_btn_nouvelle_prev) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
        }
        m->etat_btn_charger_prev = m->etat_btn_charger;
        m->etat_btn_nouvelle_prev = m->etat_btn_nouvelle;
    }
}