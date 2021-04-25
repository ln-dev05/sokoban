
/**
 * @file main.c
 * @author ln-dev05 (lord.nightmare05@gmail.com)
 * @brief Sokoban inspired by Openclassroom C course
 * @version 0.1
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "constantes.h"
#include "editeur.h"
#include "jeu.h"
#include "utils.h"

int main(int argc, char *argv[]) {
    SDL_Surface *ecran;
    SDL_Surface *menu;
    SDL_Rect position_menu = {0, 0, 0, 0};
    SDL_Event event;

    manage_input(argc, argv);
    ecran = set_up();
    menu = IMG_Load(IMG_MENU);

    while (1) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                goto _exit;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto _exit;
                    case SDLK_KP1:
                        jouer(ecran);
                        break;
                    case SDLK_KP2:
                        editeur(ecran);
                        break;
                }
                break;
        }
        clear_screen(ecran);
        SDL_BlitSurface(menu, NULL, ecran, &position_menu);
        SDL_Flip(ecran);
    }

_exit:
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    SDL_Quit();

    return EXIT_SUCCESS;
}
