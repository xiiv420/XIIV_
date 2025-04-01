#ifndef OPTIONS_MENU_H
#define OPTIONS_MENU_H

#include "../menu.h"

void init_options_menu(Menu *m);
void afficher_options_menu(Menu m, SDL_Surface *ecran);
void handle_options_input(Menu *m, SDL_Event event, SDL_Surface **ecran);

#endif