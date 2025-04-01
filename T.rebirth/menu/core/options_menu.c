#include "options_menu.h"
#include "../menu.h"
#include "utilities.h"
#include <stdio.h>

void init_options_menu(Menu *m) {
    // Load background
    m->bg_option = IMG_Load("/home/T.rebirth/menu/assets/images/2.jpg");
    if(!m->bg_option) {
        printf("Error loading options background: %s\n", IMG_GetError());
    }

    // Load button textures
    m->option_plus[0] = IMG_Load("/home/T.rebirth/menu/assets/images/increase.png");
    m->option_plus[1] = IMG_Load("/home/T.rebirth/menu/assets/images/increaser.png");
    m->option_moin[0] = IMG_Load("/home/T.rebirth/menu/assets/images/decrease.png");
    m->option_moin[1] = IMG_Load("/home/T.rebirth/menu/assets/images/decreaser.png");
    m->option_retour[0] = IMG_Load("/home/T.rebirth/menu/assets/images/back.png");
    m->option_retour[1] = IMG_Load("/home/T.rebirth/menu/assets/images/backr.png");
    m->option_normal[0] = IMG_Load("/home/T.rebirth/menu/assets/images/normal.png");
    m->option_normal[1] = IMG_Load("/home/T.rebirth/menu/assets/images/normalr.png");
    m->option_plein[0] = IMG_Load("/home/T.rebirth/menu/assets/images/full.png");
    m->option_plein[1] = IMG_Load("/home/T.rebirth/menu/assets/images/fullr.png");

    // Set button positions
    m->pos_plus = (SDL_Rect){967, 320, m->option_plus[0]->w, m->option_plus[0]->h};
    m->pos_moin = (SDL_Rect){1372, 320, m->option_moin[0]->w, m->option_moin[0]->h};
    m->pos_normal = (SDL_Rect){967, 550, m->option_normal[0]->w, m->option_normal[0]->h};
    m->pos_plein = (SDL_Rect){1372, 550, m->option_plein[0]->w, m->option_plein[0]->h};
    m->pos_retour = (SDL_Rect){1384, 756, m->option_retour[0]->w, m->option_retour[0]->h};
}

void afficher_options_menu(Menu m, SDL_Surface *ecran) {
    // Draw background
    SDL_BlitSurface(m.bg_option, NULL, ecran, NULL);

    // Volume controls
    SDL_BlitSurface(
        collision_avec_souris(m.pos_moin) ? m.option_moin[1] : m.option_moin[0],
        NULL, ecran, &m.pos_moin
    );
    
    SDL_BlitSurface(
        collision_avec_souris(m.pos_plus) ? m.option_plus[1] : m.option_plus[0],
        NULL, ecran, &m.pos_plus
    );

    // Screen mode buttons
    SDL_BlitSurface(
        collision_avec_souris(m.pos_normal) ? m.option_normal[1] : m.option_normal[0],
        NULL, ecran, &m.pos_normal
    );
    
    SDL_BlitSurface(
        collision_avec_souris(m.pos_plein) ? m.option_plein[1] : m.option_plein[0],
        NULL, ecran, &m.pos_plein
    );

    // Back button
    SDL_BlitSurface(
        collision_avec_souris(m.pos_retour) ? m.option_retour[1] : m.option_retour[0],
        NULL, ecran, &m.pos_retour
    );
}

void handle_options_input(Menu *m, SDL_Event event, SDL_Surface **ecran) {
    if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
        // Volume decrease
        if(collision_avec_souris(m->pos_moin)) {
            m->volume_music = (m->volume_music - 10 < 0) ? 0 : m->volume_music - 10;
            Mix_VolumeMusic(m->volume_music);
            printf("Volume: %d\n", m->volume_music);
        }
        // Volume increase
        else if(collision_avec_souris(m->pos_plus)) {
            m->volume_music = (m->volume_music + 10 > 100) ? 100 : m->volume_music + 10;
            Mix_VolumeMusic(m->volume_music);
            printf("Volume: %d\n", m->volume_music);
        }
        // Toggle fullscreen
        else if(collision_avec_souris(m->pos_plein) && !m->etat_plein_ecran) {
            SDL_Surface* new_ecran = SDL_SetVideoMode(1920, 1080, 32, 
                SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
            if(new_ecran) {
                m->etat_plein_ecran = 1;
                printf("Switched to fullscreen\n");
            }
        }
        // Toggle windowed
        else if(collision_avec_souris(m->pos_normal) && m->etat_plein_ecran) {
            SDL_Surface* new_ecran = SDL_SetVideoMode(1920, 1080, 32, 
                SDL_HWSURFACE | SDL_DOUBLEBUF);
            if(new_ecran) {
                m->etat_plein_ecran = 0;
                printf("Switched to windowed\n");
            }
        }
    }
}