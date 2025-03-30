#include "header.h"

int bg_x = 0;


int main() {
    

    Player player;
    int running = 1;

    if (initBackground() < 0) return 1;
    init_player(&player);

    while (running) {
        handle_input(&running, &player);
        update_player(&player);

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));  // Clear the screen// Render score without SDL_ttf
        renderBackground(bg_x);
        render_player(&player);

        SDL_Flip(screen);  // Update the screen after drawing everything
        SDL_Delay(16);
    }

    cleanupBackground();
    return 0;
}
