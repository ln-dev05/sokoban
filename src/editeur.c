
#include "editeur.h"

#include "constantes.h"
#include "fichiers.h"

void editeur(SDL_Surface *ecran) {
    SDL_Surface *vide = IMG_Load(IMG_VIDE);
    SDL_Surface *mur = IMG_Load(IMG_MUR);
    SDL_Surface *caisse = IMG_Load(IMG_CAISSE);
    SDL_Surface *objectif = IMG_Load(IMG_OBJ);
    SDL_Surface *mario = IMG_Load(IMG_A_B);
    SDL_Surface *caisseOK = IMG_Load(IMG_CAISSE_OK);
    SDL_Surface *objActuel = mur;
    SDL_Rect posObjectAct;
    SDL_Event event;

    int clicGaucheEnCours = 0;
    int clicDroitEnCours = 0;
    int objetActuel = MUR;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR];

    if (!chargerNiveau(carte)) exit(EXIT_FAILURE);

    while (1) {
        SDL_WaitEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                goto _exit;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                    clicGaucheEnCours = 1;
                } else if (event.button.button == SDL_BUTTON_RIGHT) {
                    carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;
            case SDL_MOUSEMOTION:
                posObjectAct.x = event.motion.x;
                posObjectAct.y = event.motion.y;
                if (clicGaucheEnCours) {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                } else if (clicDroitEnCours) {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        goto _exit;
                        break;
                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;
                    case SDLK_KP1:
                        objetActuel = MUR;
                        objActuel = mur;
                        break;
                    case SDLK_KP2:
                        objetActuel = CAISSE;
                        objActuel = caisse;
                        break;
                    case SDLK_KP3:
                        objetActuel = OBJECTIF;
                        objActuel = objectif;
                        break;
                    case SDLK_KP4:
                        objetActuel = MARIO;
                        objActuel = mario;
                        break;
                    case SDLK_KP5:
                        objetActuel = CAISSE_OK;
                        objActuel = caisseOK;
                        break;
                    case SDLK_KP_MINUS:
                        goto _exit;
                        modifLvl(2);
                        editeur(ecran);
                        break;
                    case SDLK_KP_PLUS:
                        goto _exit;
                        modifLvl(1);
                        editeur(ecran);
                        break;
                }
                break;
        }

        clear_screen(ecran);
        editor_display(ecran, carte, posObjectAct, vide, mur, caisse, objectif, mario, caisseOK, objActuel);
    }

_exit:
    SDL_FreeSurface(mur);
    SDL_FreeSurface(caisse);
    SDL_FreeSurface(objectif);
    SDL_FreeSurface(mario);
    SDL_FreeSurface(caisseOK);
    SDL_FreeSurface(vide);
}
