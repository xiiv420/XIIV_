#include <SDL/SDL.h>
#include "header.h"

extern SDL_Surface *screen;

int gameOverScreen(SDL_Surface *screen) {
    SDL_Surface *background = SDL_LoadBMP("/home/T.rebirth/images/gameover/gameover.bmp");
    SDL_Surface *yesOption = SDL_LoadBMP("/home/T.rebirth/images/gameover/yes.bmp");
    SDL_Surface *noOption = SDL_LoadBMP("/home/T.rebirth/images/gameover/no.bmp");

    if (!background || !yesOption || !noOption) {
        printf("Error loading images: %s\n", SDL_GetError());
        return 0;
    }

    SDL_Rect yesPos = {100, 400, 0, 0};
    SDL_Rect noPos = {500, 400, 0, 0};

    int selected = 0;
    int running = 1;
    SDL_Event event;

    SDL_Surface *fadeScreen = SDL_CreateRGBSurface(0, screen->w, screen->h, 32, 0, 0, 0, 0);
    SDL_SetAlpha(fadeScreen, SDL_SRCALPHA, 255);  

    // **Smooth Fade-in effect**
    for (int alpha = 255; alpha >= 0; alpha -= 5) {
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));

        SDL_BlitSurface(background, NULL, screen, NULL);
        SDL_BlitSurface(yesOption, NULL, screen, &yesPos);
        SDL_BlitSurface(noOption, NULL, screen, &noPos);

        SDL_SetAlpha(fadeScreen, SDL_SRCALPHA, alpha);
        SDL_BlitSurface(fadeScreen, NULL, screen, NULL);

        SDL_Flip(screen);
        SDL_Delay(30);
    }
    SDL_FreeSurface(fadeScreen);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) return 0;

            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT: selected = 0; break;
                    case SDLK_RIGHT: selected = 1; break;
                    case SDLK_RETURN:
                        if (selected == 0) {
                            // **Restart the game** without exiting
                            SDL_FreeSurface(background);
                            SDL_FreeSurface(yesOption);
                            SDL_FreeSurface(noOption);
                            return 1;  // **Signal restart**
                        } else {
                            // **Quit the game**
                            SDL_FreeSurface(background);
                            SDL_FreeSurface(yesOption);
                            SDL_FreeSurface(noOption);
                            return 0;
                        }
                }
            }

            if (event.type == SDL_MOUSEMOTION) {
                int mouseX = event.motion.x + 10, mouseY = event.motion.y; // **Moved 10px more right**
                if (mouseX >= yesPos.x - 10 && mouseX <= yesPos.x + 100 &&
                    mouseY >= yesPos.y - 5 && mouseY <= yesPos.y + 35) {
                    selected = 0;
                } else if (mouseX >= noPos.x - 10 && mouseX <= noPos.x + 100 &&
                           mouseY >= noPos.y - 5 && mouseY <= noPos.y + 35) {
                    selected = 1;
                }
            }

            if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                int mouseX = event.button.x, mouseY = event.button.y;

                // **Only trigger selection if clicking inside a button**
                if (mouseX >= yesPos.x - 10 && mouseX <= yesPos.x + 100 &&
                    mouseY >= yesPos.y - 5 && mouseY <= yesPos.y + 35) {
                    SDL_FreeSurface(background);
                    SDL_FreeSurface(yesOption);
                    SDL_FreeSurface(noOption);
                    return 1;  // **Restart game**
                }

                if (mouseX >= noPos.x - 10 && mouseX <= noPos.x + 100 &&
                    mouseY >= noPos.y - 5 && mouseY <= noPos.y + 35) {
                    SDL_FreeSurface(background);
                    SDL_FreeSurface(yesOption);
                    SDL_FreeSurface(noOption);
                    return 0;  // **Quit game**
                }
            }
        }

        SDL_BlitSurface(background, NULL, screen, NULL);
        SDL_BlitSurface(yesOption, NULL, screen, &yesPos);
        SDL_BlitSurface(noOption, NULL, screen, &noPos);

        // **Indicator above the selected button (now taller and white)**
        SDL_Rect indicator = {
            selected == 0 ? yesPos.x + 30 : noPos.x + 30, 
            selected == 0 ? yesPos.y - 15 : noPos.y - 15, 
            20, 
            8  // **Taller indicator**
        };

        SDL_FillRect(screen, &indicator, SDL_MapRGB(screen->format, 255, 255, 255)); 

        SDL_Flip(screen);
        SDL_Delay(100);
    }

    return 0;
}
