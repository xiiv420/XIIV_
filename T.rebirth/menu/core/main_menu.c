#include "main_menu.h"
#include "../menu.h"
#include "utilities.h"
#include <stdio.h>

void init_main_menu(Menu *m) {
    // Load background
    m->bg_principal = IMG_Load("/home/T.rebirth/menu/assets/images/1.jpg");
    if(!m->bg_principal) {
        printf("Error loading main background: %s\n", IMG_GetError());
    }

    // Load button textures
    m->jouer_btn[0] = IMG_Load("/home/T.rebirth/menu/assets/images/start.png");
    m->jouer_btn[1] = IMG_Load("/home/T.rebirth/menu/assets/images/startr.png");
    m->option_btn[0] = IMG_Load("/home/T.rebirth/menu/assets/images/setting.png");
    m->option_btn[1] = IMG_Load("/home/T.rebirth/menu/assets/images/settingr.png");
    m->meilleur_btn[0] = IMG_Load("/home/T.rebirth/menu/assets/images/best.png");
    m->meilleur_btn[1] = IMG_Load("/home/T.rebirth/menu/assets/images/bestr.png");
    m->histoire_btn[0] = IMG_Load("/home/T.rebirth/menu/assets/images/exit.png");
    m->histoire_btn[1] = IMG_Load("/home/T.rebirth/menu/assets/images/exitr.png");
    m->quit_btn[0] = IMG_Load("/home/T.rebirth/menu/assets/images/exit.png");
    m->quit_btn[1] = IMG_Load("/home/T.rebirth/menu/assets/images/exitr.png");

    // Calculate button positions
    m->pos_btn_jouer.x = (1920/2) - (m->jouer_btn[0]->w/2);
    m->pos_btn_jouer.y = 100;
    m->pos_btn_jouer.w = m->jouer_btn[0]->w;
    m->pos_btn_jouer.h = m->jouer_btn[0]->h;

    m->pos_btn_option.x = (1920/2) - (m->option_btn[0]->w/2);
    m->pos_btn_option.y = 200;
    m->pos_btn_option.w = m->option_btn[0]->w;
    m->pos_btn_option.h = m->option_btn[0]->h;

    m->pos_btn_meilleur.x = (1920/2) - (m->meilleur_btn[0]->w/2);
    m->pos_btn_meilleur.y = 300;
    m->pos_btn_meilleur.w = m->meilleur_btn[0]->w;
    m->pos_btn_meilleur.h = m->meilleur_btn[0]->h;

    m->pos_btn_histoire.x = (1920/2) - (m->histoire_btn[0]->w/2);
    m->pos_btn_histoire.y = 400;
    m->pos_btn_histoire.w = m->histoire_btn[0]->w;
    m->pos_btn_histoire.h = m->histoire_btn[0]->h;

    m->pos_btn_quit.x = (1920/2) - (m->quit_btn[0]->w/2);
    m->pos_btn_quit.y = 500;
    m->pos_btn_quit.w = m->quit_btn[0]->w;
    m->pos_btn_quit.h = m->quit_btn[0]->h;

    // Load font and text
    m->arial = TTF_OpenFont("/home/T.rebirth/menu/assets/font/pixel.ttf", 40);
    if(!m->arial) {
        printf("Failed to load font: %s\n", TTF_GetError());
    }
    
    m->textColor = (SDL_Color){255, 0, 0, 0};
    m->titreJeu = TTF_RenderText_Solid(m->arial, "THE REBIRTH", m->textColor);
    m->posTitre = (SDL_Rect){1500, 220, m->titreJeu->w, m->titreJeu->h};

    // Load logo
    m->logo = IMG_Load("/home/T.rebirth/menu/assets/images/logo.png");
    if(!m->logo) {
        printf("Error loading logo: %s\n", IMG_GetError());
    }
    m->posLogo = (SDL_Rect){1590, 30, m->logo->w, m->logo->h};

    // Load background music
    m->background_music = Mix_LoadMUS("/home/T.rebirth/menu/assets/sound/music.mp3");
    if(!m->background_music) {
        printf("Error loading music: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(m->background_music, -1);
    }
}

void afficher_main_menu(Menu m, SDL_Surface *ecran) {
    // Draw background
    SDL_BlitSurface(m.bg_principal, NULL, ecran, NULL);

    // Draw buttons with hover states
    SDL_BlitSurface(
        (collision_avec_souris(m.pos_btn_jouer) || m.btn_selectionner == 1) ? 
        m.jouer_btn[1] : m.jouer_btn[0], 
        NULL, ecran, &m.pos_btn_jouer
    );

    SDL_BlitSurface(
        (collision_avec_souris(m.pos_btn_option) || m.btn_selectionner == 2) ? 
        m.option_btn[1] : m.option_btn[0], 
        NULL, ecran, &m.pos_btn_option
    );

    SDL_BlitSurface(
        (collision_avec_souris(m.pos_btn_meilleur) || m.btn_selectionner == 3) ? 
        m.meilleur_btn[1] : m.meilleur_btn[0], 
        NULL, ecran, &m.pos_btn_meilleur
    );

    SDL_BlitSurface(
        (collision_avec_souris(m.pos_btn_histoire) || m.btn_selectionner == 4) ? 
        m.histoire_btn[1] : m.histoire_btn[0], 
        NULL, ecran, &m.pos_btn_histoire
    );

    SDL_BlitSurface(
        (collision_avec_souris(m.pos_btn_quit) || m.btn_selectionner == 5) ? 
        m.quit_btn[1] : m.quit_btn[0], 
        NULL, ecran, &m.pos_btn_quit
    );

    // Draw text elements
    SDL_BlitSurface(m.titreJeu, NULL, ecran, &m.posTitre);
    SDL_BlitSurface(m.logo, NULL, ecran, &m.posLogo);
}

void miseajour_main_menu(Menu *m) {
    // Update button selection states
    if(collision_avec_souris(m->pos_btn_jouer)) {
        if(m->btn_selectionner != 1) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
            m->btn_selectionner = 1;
        }
    }
    else if(collision_avec_souris(m->pos_btn_option)) {
        if(m->btn_selectionner != 2) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
            m->btn_selectionner = 2;
        }
    }
    else if(collision_avec_souris(m->pos_btn_meilleur)) {
        if(m->btn_selectionner != 3) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
            m->btn_selectionner = 3;
        }
    }
    else if(collision_avec_souris(m->pos_btn_histoire)) {
        if(m->btn_selectionner != 4) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
            m->btn_selectionner = 4;
        }
    }
    else if(collision_avec_souris(m->pos_btn_quit)) {
        if(m->btn_selectionner != 5) {
            Mix_PlayChannel(-1, m->son_btn_selecter, 0);
            m->btn_selectionner = 5;
        }
    }
}