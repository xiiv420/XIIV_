#include "utilities.h"

int collision_avec_souris(SDL_Rect pos_btn) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    return (x >= pos_btn.x && x <= pos_btn.x + pos_btn.w &&
            y >= pos_btn.y && y <= pos_btn.y + pos_btn.h);
}