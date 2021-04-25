#include "jeu.h"

#include "constantes.h"

void jouer(SDL_Surface *ecran) {
    SDL_Surface *mario[4];
    SDL_Surface *mur;
    SDL_Surface *caisse;
    SDL_Surface *caisseOK;
    SDL_Surface *objectif;
    SDL_Surface *marioActuel;
    SDL_Surface *vide;
    SDL_Surface *bravo;
    SDL_Surface *decor[6];
    SDL_Rect position;
    SDL_Rect positionJoueur;
    SDL_Rect positionLegende;
    SDL_Event event;

    int continuer = 1;
    int objectifsRestants = 0;
    int i = 0;
    int j = 0;
    int continuer2 = 1;
    int verif = 0;
    int spriteLegend;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {MUR};

    srand(time(NULL));

    mur = IMG_Load(IMG_MUR);
    caisse = IMG_Load(IMG_CAISSE);
    caisseOK = IMG_Load(IMG_CAISSE_OK);
    objectif = IMG_Load(IMG_OBJ);
    mario[BAS] = IMG_Load(IMG_A_B);
    mario[GAUCHE] = IMG_Load(IMG_A_G);
    mario[HAUT] = IMG_Load(IMG_A_H);
    mario[DROITE] = IMG_Load(IMG_A_D);
    vide = IMG_Load(IMG_VIDE);
    bravo = IMG_Load(IMG_BRAVO);
    decor[HEATRAN] = IMG_Load(IMG_DECOR_0);
    decor[DARKRAI] = IMG_Load(IMG_DECOR_1);
    decor[CRESSELIA] = IMG_Load(IMG_DECOR_2);
    decor[CREFOLLET] = IMG_Load(IMG_DECOR_3);
    decor[CREHELF] = IMG_Load(IMG_DECOR_4);
    decor[CREFADET] = IMG_Load(IMG_DECOR_5);

    spriteLegend = rand() % 6;
    marioActuel = mario[BAS];

    if (!chargerNiveau(carte, 'r'))
        exit(EXIT_FAILURE);
    for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
            if (carte[i][j] == MARIO) {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    positionLegende.x = (rand() % (NB_BLOCS_LARGEUR + 1)) * TAILLE_BLOC;
    positionLegende.y = (rand() % (NB_BLOCS_HAUTEUR + 1)) * TAILLE_BLOC;

    SDL_EnableKeyRepeat(100, 100);

    while (continuer) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;
                    case SDLK_UP:
                        marioActuel = mario[HAUT];
                        deplacerJoueur(carte, &positionJoueur, HAUT);
                        break;
                    case SDLK_DOWN:
                        marioActuel = mario[BAS];
                        deplacerJoueur(carte, &positionJoueur, BAS);
                        break;
                    case SDLK_RIGHT:
                        marioActuel = mario[DROITE];
                        deplacerJoueur(carte, &positionJoueur, DROITE);
                        break;
                    case SDLK_LEFT:
                        marioActuel = mario[GAUCHE];
                        deplacerJoueur(carte, &positionJoueur, GAUCHE);
                        break;
                    case SDLK_r:
                        continuer = 0;
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        jouer(ecran);
                        break;
                    case SDLK_KP_MINUS:
                        continuer = 0;
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        modifLvl(2);
                        jouer(ecran);
                        break;
                    case SDLK_KP_PLUS:
                        continuer = 0;
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        modifLvl(1);
                        jouer(ecran);
                        break;
                }
                break;
        }

        clear_screen(ecran);

        objectifsRestants = 0;

        for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
            for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch (carte[i][j]) {
                    case MUR:
                        SDL_BlitSurface(mur, NULL, ecran, &position);
                        break;
                    case CAISSE:
                        SDL_BlitSurface(caisse, NULL, ecran, &position);
                        break;
                    case CAISSE_OK:
                        SDL_BlitSurface(caisseOK, NULL, ecran, &position);
                        break;
                    case OBJECTIF:
                        SDL_BlitSurface(objectif, NULL, ecran, &position);
                        objectifsRestants = 1;
                        break;
                    case VIDE:
                        SDL_BlitSurface(vide, NULL, ecran, &position);
                        break;
                }
            }
        }

        SDL_BlitSurface(decor[spriteLegend], NULL, ecran, &positionLegende);

        if (!verif && !objectifsRestants)
            exit(EXIT_FAILURE);

        if (!objectifsRestants) {
            continuer = 0;
            while (continuer2) {
                SDL_WaitEvent(&event);
                position.x = ecran->w / 2 - bravo->w / 2;
                position.y = ecran->h / 2 - bravo->h / 2;
                SDL_BlitSurface(bravo, NULL, ecran, &position);
                modifLvl(1);
                SDL_Flip(ecran);
                SDL_WaitEvent(&event);
                switch (event.type) {
                    case SDL_QUIT:
                        continuer2 = 0;
                        break;
                    case SDL_MOUSEBUTTONDOWN:
                        continuer2 = 0;
                        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                        jouer(ecran);
                        break;
                    case SDL_KEYDOWN:
                        switch (event.key.keysym.sym) {
                            case SDLK_ESCAPE:
                                continuer2 = 0;
                                break;
                            case SDLK_r:
                                continuer2 = 0;
                                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                                jouer(ecran);
                                break;
                            case SDLK_SPACE:
                                continuer2 = 0;
                                SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));
                                jouer(ecran);
                                break;
                            case SDLK_RETURN:
                                continuer2 = 0;
                                break;
                        }
                }
            }
        }

        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;
        SDL_BlitSurface(marioActuel, NULL, ecran, &position);

        verif = 1;
        SDL_Flip(ecran);
    }

    SDL_EnableKeyRepeat(0, 0);

    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(vide);
    SDL_FreeSurface(bravo);
    for (i = 0; i < 4; i++)
        SDL_FreeSurface(mario[i]);
    for (i = 0; i < 6; i++)
        SDL_FreeSurface(decor[i]);
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction) {
    switch (direction) {
        case HAUT:
            if (pos->y - 1 < 0)
                break;
            if (carte[pos->x][pos->y - 1] == MUR)
                break;
            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR ||
                 carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
                break;

            r
                deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);

            pos->y--;
            break;

        case BAS:
            if (pos->y + 1 >= NB_BLOCS_HAUTEUR)
                break;
            if (carte[pos->x][pos->y + 1] == MUR)
                break;

            if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
                (pos->y + 2 >= NB_BLOCS_HAUTEUR || carte[pos->x][pos->y + 2] == MUR ||
                 carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
                break;

            deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);

            pos->y++;
            break;

        case GAUCHE:
            if (pos->x - 1 < 0)
                break;
            if (carte[pos->x - 1][pos->y] == MUR)
                break;

            if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y] == CAISSE_OK) &&
                (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR ||
                 carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
                break;

            deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);

            pos->x--;
            break;

        case DROITE:
            if (pos->x + 1 >= NB_BLOCS_LARGEUR)
                break;
            if (carte[pos->x + 1][pos->y] == MUR)
                break;

            if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y] == CAISSE_OK) &&
                (pos->x + 2 >= NB_BLOCS_LARGEUR || carte[pos->x + 2][pos->y] == MUR ||
                 carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
                break;

            deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);

            pos->x++;
            break;
    }
}

void deplacerCaisse(int *premiereCase, int *secondeCase) {
    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK) {
        if (*secondeCase == OBJECTIF)
            *secondeCase = CAISSE_OK;
        else
            *secondeCase = CAISSE;

        if (*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
    }
}
