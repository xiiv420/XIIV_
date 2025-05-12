#ifndef ENIGME_H
#define ENIGME_H

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>

#define MAX_QUESTIONS 100

/**
 * @struct enigme
 * @brief Structure représentant une énigme dans le jeu
 */
typedef struct {
    char question[100]; /*!< Question à poser à l'utilisateur */
    char r1[50], r2[50], r3[50]; /*!< Réponses possibles */
    int numQuestSelect; /*!< Numéro de la question sélectionnée */
    int bonne; /*!< Indicateur de la bonne réponse (1 = correcte, 0 = incorrecte) */

    SDL_Surface *surface_question; /*!< Surface contenant la question */
    SDL_Surface *surface_rep1; /*!< Surface pour la première réponse */
    SDL_Surface *surface_rep2; /*!< Surface pour la deuxième réponse */
    SDL_Surface *surface_rep3; /*!< Surface pour la troisième réponse */

    SDL_Rect pos_question; /*!< Position de la question */
    SDL_Rect pos_rep1; /*!< Position de la première réponse */
    SDL_Rect pos_rep2; /*!< Position de la deuxième réponse */
    SDL_Rect pos_rep3; /*!< Position de la troisième réponse */

    TTF_Font *font; /*!< Police utilisée pour le texte */
    SDL_Color textColor; /*!< Couleur du texte */

    int tempsActuel, tempsPrecedent, compteur; /*!< Variables de gestion du temps */
    SDL_Surface *afficherTemps; /*!< Surface affichant le temps restant */
    SDL_Rect positionTemps; /*!< Position de l'affichage du temps */

    int etat_enigme; /*!< État de l'énigme (par exemple, en cours, résolue) */
} enigme;



void Init_Enigme(enigme *e);
void Afficherenigme(enigme *e, SDL_Surface *screen);

enigme generer(char *nom_du_fichier);

int resolution_enigme(SDL_Surface *screen, SDL_Surface *background, enigme *e, int *score, Mix_Chunk *win, Mix_Chunk *lose, Mix_Chunk *clickSound);

void afficher_timer(SDL_Surface *screen, enigme *e);

void afficher_message(SDL_Surface *screen, SDL_Surface *background, char* texte_a_afficher, SDL_Color couleur, Mix_Chunk *sound);

void Libererenigme(enigme *e);

#endif

