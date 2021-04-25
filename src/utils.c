#include "utils.h"

inline void clear_screen(SDL_Surface *ecran) {
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
}

inline SDL_Surface *set_up() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_WM_SetIcon(IMG_Load(IMG_ICON), NULL);
    SDL_WM_SetCaption(TXT_TITLE, NULL);
    return SDL_SetVideoMode(LARGEUR_FENETRE, HAUTEUR_FENETRE, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
}

inline void manage_input(int argc, char *argv[]) {
    if (argc == 0 || !argv) {
        exit(EXIT_FAILURE);
    }
}

inline void editor_display(SDL_Surface *ecran, int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR],
                           SDL_Rect posObjectAct, SDL_Surface *vide, SDL_Surface *mur,
                           SDL_Surface *caisse, SDL_Surface *objectif, SDL_Surface *mario,
                           SDL_Surface *caisseOK, SDL_Surface *objActuel) {
    SDL_Rect position;
    SDL_Surface *surfaces[CAISSE_OK + 1] = {vide,
                                            mur,
                                            caisse,
                                            objectif,
                                            mario,
                                            caisseOK};

    int i = 0;
    int j = 0;

    for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
            position.x = i * TAILLE_BLOC;
            position.y = j * TAILLE_BLOC;
            SDL_BlitSurface(surfaces[carte[i][j] % 6], NULL, ecran, &position);
        }
    }
    SDL_BlitSurface(objActuel, NULL, ecran, &posObjectAct);
    SDL_Flip(ecran);
}