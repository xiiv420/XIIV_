#include "menu.h"
#include "core/main_menu.h"
#include "core/options_menu.h"
#include "core/save_menu.h"
#include "core/player_menu.h"
#include "core/best_score.h"
#include "core/utilities.h"

void init_menu(Menu *m) {
    // Initialize all sub-components
    init_main_menu(m);
    init_options_menu(m);
    init_save_menu(m);
    init_player_menu(m);
    init_best_score(m);
    
    // Initialize universal properties
    m->volume_music = 50;
    m->etat_plein_ecran = 0;
    m->btn_selectionner = 0;
    
    // debuggung wav

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        exit(1);
    }
    

    // Load universal assets

    m->son_btn_selecter = Mix_LoadWAV("assets/sound/2038.wav");
    if(!m->son_btn_selecter) {
        printf("Failed to load button sound: %s\n", Mix_GetError());
    }
    
    
    // Set initial volumes
    Mix_VolumeMusic(m->volume_music);
}