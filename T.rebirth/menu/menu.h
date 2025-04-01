#ifndef MENU_H
#define MENU_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct {
    // === Main Menu Assets ===
    SDL_Surface *bg_principal;
    SDL_Surface *jouer_btn[2], *option_btn[2], *meilleur_btn[2], *histoire_btn[2], *quit_btn[2];
    SDL_Rect pos_btn_jouer, pos_btn_option, pos_btn_meilleur, pos_btn_histoire, pos_btn_quit;
    
    // === Options Menu Assets ===
    SDL_Surface *bg_option, *option_plus[2], *option_moin[2], *option_retour[2], *option_normal[2], *option_plein[2];
    SDL_Rect pos_plus, pos_moin, pos_retour, pos_normal, pos_plein;
    
    // === Save Menu Assets ===
    SDL_Surface *bg_sauvegarde, *btn_oui[2], *btn_non[2], *btn_charger[2], *btn_nouvelle[2];
    SDL_Rect pos_btn_oui, pos_btn_non, pos_btn_charger, pos_btn_nouvelle;
    
    SDL_Surface *textSauvegarde;  
    SDL_Rect PosTextSauv;         

    // === Player Menu Assets ===
    SDL_Surface *bg_joueur, *btn_mono[2], *btn_multi[2], *btn_avatar1[2], *btn_avatar2[2], *btn_input1[2], *btn_input2[2], *btn_retour[2], *btn_valider[2];
    SDL_Rect pos_btn_mono, pos_btn_multi, pos_btn_avatar1, pos_btn_avatar2, pos_btn_input1, pos_btn_input2, pos_btn_retour, pos_btn_valider;
    
    // === Best Score Menu Assets ===
    SDL_Surface *bg_meilleur, *espace_saisie[2], *etoile[3], *textNom, *textMeilleur;
    SDL_Rect pos_espace_saisie, pos_etoile[3], pos_nom, pos_meilleur;

    // === Common Assets ===
    SDL_Surface *titreJeu, *logo;
    SDL_Rect posTitre, posLogo;
    Mix_Music *background_music;
    Mix_Chunk *son_btn_selecter;
    TTF_Font *arial;
    SDL_Color textColor;
    
    // === State Variables ===
    int btn_selectionner;
    int volume_music;
    int etat_plein_ecran;
    int num_page_sauv;
    
    // ✅ Fixed and Cleaned Up
    int etat_btn_oui, etat_btn_oui_prev;
    int etat_btn_non, etat_btn_non_prev;
    int etat_btn_charger, etat_btn_charger_prev;
    int etat_btn_nouvelle, etat_btn_nouvelle_prev;

    int num_page_joueur;
    int etat_btn_mono, etat_btn_multi, etat_btn_avatar1, etat_btn_avatar2;
    int etat_btn_input1, etat_btn_input2, etat_btn_retour, etat_btn_valider;
    int num_page_meilleur;
    int etat_espace_saisie, espace_saisie_actif;

} Menu;

// Universal initialization function
void init_menu(Menu *m);
void afficher_menu_joueur(Menu m, SDL_Surface *ecran);
void miseajour_menu_joueur(Menu *m);
void afficher_menu_meilleur(Menu m, SDL_Surface *ecran);
void miseajour_menu_meilleur(Menu *m);
int collision_avec_souris(SDL_Rect pos_btn);  // Critical for input handling

#endif
