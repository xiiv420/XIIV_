#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "menu.h"
#include "core/main_menu.h"
#include "core/options_menu.h"
#include "core/save_menu.h"
#include "core/player_menu.h"
#include "core/best_score.h"

int main() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    SDL_Surface *ecran = SDL_SetVideoMode(1920, 1080, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096);
    TTF_Init();

    int quitter = 0;
    SDL_Event event;
    int indice_ecran = 0;
    Menu menu;
    init_menu(&menu);

    while (!quitter) {
        switch(indice_ecran) {
            case 0:  // Main Menu
                afficher_main_menu(menu, ecran);
                SDL_Flip(ecran);
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            quitter = 1;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                if(menu.btn_selectionner == 5) quitter = 1;
                                if(menu.btn_selectionner == 1) indice_ecran = 3;
                                if(menu.btn_selectionner == 2) indice_ecran = 2;
                                if(menu.btn_selectionner == 3) indice_ecran = 4;
                            }
                            break;
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_DOWN) {
                                menu.btn_selectionner++;
                                if(menu.btn_selectionner > 5) menu.btn_selectionner = 1;
                            }
                            if(event.key.keysym.sym == SDLK_UP) {
                                menu.btn_selectionner--;
                                if(menu.btn_selectionner < 1) menu.btn_selectionner = 5;
                            }
                            if(event.key.keysym.sym == SDLK_j || (menu.btn_selectionner == 1 && event.key.keysym.sym == SDLK_RETURN)) {
                                indice_ecran = 1;
                            }
                            if(event.key.keysym.sym == SDLK_o || (menu.btn_selectionner == 2 && event.key.keysym.sym == SDLK_RETURN)) {
                                indice_ecran = 2;
                            }
                            if(event.key.keysym.sym == SDLK_m || (menu.btn_selectionner == 3 && event.key.keysym.sym == SDLK_RETURN)) {
                                indice_ecran = 3;
                            }
                            break;
                    }
                }
                miseajour_main_menu(&menu);
                break;

            case 1:  // Player Menu
                afficher_player_menu(menu, ecran);
                SDL_Flip(ecran);
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            quitter = 1;
                            break;
                        case SDL_KEYDOWN:
                            indice_ecran = 0;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                if(menu.etat_btn_retour == 1) {
                                    if(menu.num_page_joueur == 0) indice_ecran = 0;
                                    else menu.num_page_joueur = 0;
                                }
                                if(menu.etat_btn_mono == 1 || menu.etat_btn_multi == 1) {
                                    menu.num_page_joueur = 1;
                                    menu.etat_btn_mono = 0;
                                    menu.etat_btn_multi = 0;
                                }
                                // Handle avatar selection
                                if(collision_avec_souris(menu.pos_btn_avatar1)) {
                                    menu.etat_btn_avatar1 = 1;
                                    menu.etat_btn_avatar2 = 0;
                                }
                                else if(collision_avec_souris(menu.pos_btn_avatar2)) {
                                    menu.etat_btn_avatar1 = 0;
                                    menu.etat_btn_avatar2 = 1;
                                }
                                // Handle validation
                                if(menu.etat_btn_valider == 1) indice_ecran = 4;
                            }
                            break;
                    }
                }
                miseajour_player_menu(&menu);
                break;

            case 2:  // Options Menu
                afficher_options_menu(menu, ecran);
                SDL_Flip(ecran);
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quitter = 1;
                    if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                        handle_options_input(&menu, event, &ecran);

                    }
                }
                break;

            case 3:
                printf("Checking menu elements before afficher_save_menu...\n");
                if (!menu.bg_sauvegarde) printf("bg_sauvegarde is NULL!\n");
                if (!menu.textSauvegarde) printf("textSauvegarde is NULL!\n");
                if (!menu.btn_oui[menu.etat_btn_oui]) printf("btn_oui[%d] is NULL!\n", menu.etat_btn_oui);
                if (!menu.btn_non[menu.etat_btn_non]) printf("btn_non[%d] is NULL!\n", menu.etat_btn_non);
                if (!menu.btn_charger[menu.etat_btn_charger]) printf("btn_charger[%d] is NULL!\n", menu.etat_btn_charger);
                if (!menu.btn_nouvelle[menu.etat_btn_nouvelle]) printf("btn_nouvelle[%d] is NULL!\n", menu.etat_btn_nouvelle);
                
                // Save Menu
                afficher_save_menu(&menu, ecran);


                
                SDL_Flip(ecran);
                while (SDL_PollEvent(&event)) {
                    switch (event.type) {
                        case SDL_QUIT:
                            quitter = 1;
                            break;
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_n) indice_ecran = 1;
                            break;
                        case SDL_MOUSEBUTTONDOWN:
                            if (event.button.button == SDL_BUTTON_LEFT) {
                                if(menu.etat_btn_oui == 1) menu.num_page_sauv = 1;
                                if(menu.etat_btn_nouvelle == 1) indice_ecran = 1;
                            }
                            break;
                    }
                }
                miseajour_save_menu(&menu);
                break;

            case 4:  // Best Scores
                afficher_best_score(menu, ecran);
                SDL_Flip(ecran);
                while (SDL_PollEvent(&event)) {
                    if (event.type == SDL_QUIT) quitter = 1;
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        if(collision_avec_souris(menu.pos_espace_saisie)) {
                            menu.espace_saisie_actif = 1;
                        } else {
                            menu.espace_saisie_actif = 0;
                        }
                    }
                }
                miseajour_best_score(&menu);
                break;
        }
    }

    SDL_FreeSurface(ecran);
    SDL_Quit();
    return 0;
}