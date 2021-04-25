
/**
 * @brief Define all the constants used in this project
 * 
 */
#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

#define TAILLE_BLOC         34
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define LARGEUR_FENETRE     TAILLE_BLOC* NB_BLOCS_LARGEUR
#define HAUTEUR_FENETRE     TAILLE_BLOC* NB_BLOCS_HAUTEUR

#define IMG_MENU         "img/menu.jpg"
#define IMG_ICON         "img/pok.ICO"
#define IMG_MUR          "img/mur.jpg"
#define IMG_CAISSE       "img/caisse.jpg"
#define IMG_CAISSE_OK    "img/caisse_ok.jpg"
#define IMG_OBJ          "img/objectif.png"
#define IMG_A_B          "img/ash_bas.gif"
#define IMG_A_G          "img/ash_gauche.gif"
#define IMG_A_H          "img/ash_haut.gif"
#define IMG_A_D          "img/ash_droite.gif"
#define IMG_VIDE         "img/vide.jpg"
#define IMG_BRAVO        "img/bravo.png"
#define IMG_DECOR_0      "img/decor0.png"
#define IMG_DECOR_1      "img/decor1.png"
#define IMG_DECOR_2      "img/decor2.png"
#define IMG_DECOR_3      "img/decor3.png"
#define IMG_DECOR_4      "img/decor4.png"
#define IMG_DECOR_5      "img/decor5.png"

#define TXT_TITLE "pokemon Sokoban"

#define DATA_LVL "lvl/niveaux.lvl"

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

enum {
    HAUT,
    BAS,
    GAUCHE,
    DROITE
};
enum {
    VIDE,
    MUR,
    CAISSE,
    OBJECTIF,
    MARIO,
    CAISSE_OK
};
enum {
    HEATRAN,
    DARKRAI,
    CRESSELIA,
    CREFOLLET,
    CREHELF,
    CREFADET
};

#endif
