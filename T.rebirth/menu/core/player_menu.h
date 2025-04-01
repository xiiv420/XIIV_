#ifndef PLAYER_MENU_H
#define PLAYER_MENU_H

#include "../menu.h"

void init_player_menu(Menu *m);
void afficher_player_menu(Menu m, SDL_Surface *ecran);
void miseajour_player_menu(Menu *m);

#endif