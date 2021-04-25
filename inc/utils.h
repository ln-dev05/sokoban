#ifndef DEF_UTILS
#define DEF_UTILS

#include "constantes.h"

void clear_screen(SDL_Surface *ecran);
SDL_Surface *set_up();
void manage_input(int argc, char *argv[]);
void editor_display(SDL_Surface *ecran,
                    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR],
                    SDL_Rect posObjectAct,
                    SDL_Surface *vide,
                    SDL_Surface *mur,
                    SDL_Surface *caisse,
                    SDL_Surface *objectif,
                    SDL_Surface *mario,
                    SDL_Surface *caisseOK,
                    SDL_Surface *objActuel);
#endif