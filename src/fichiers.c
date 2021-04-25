
#include "fichiers.h"

#include "constantes.h"

static int lvl = 0;

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR]) {
    FILE* fichier;
    char ligneFichier[NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1];
    int i = 0;
    int j = 0;

    fichier = fopen(DATA_LVL, "r");

    if (!fichier) return 0;

    fseek(fichier, ((NB_BLOCS_HAUTEUR * NB_BLOCS_LARGEUR + 1) * lvl), SEEK_SET);

    fgets(ligneFichier, (NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1), fichier);

    if (fgets(ligneFichier, NB_BLOCS_LARGEUR * NB_BLOCS_HAUTEUR + 1, fichier) == NULL)
        return 0;

    for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
            switch (ligneFichier[(i * NB_BLOCS_LARGEUR) + j]) {
                case '0':
                    niveau[j][i] = VIDE;
                    break;
                case '1':
                    niveau[j][i] = MUR;
                    break;
                case '2':
                    niveau[j][i] = CAISSE;
                    break;
                case '3':
                    niveau[j][i] = OBJECTIF;
                    break;
                case '4':
                    niveau[j][i] = MARIO;
                    break;
                case '5':
                    niveau[j][i] = CAISSE_OK;
                    break;
            }
        }
    }

    fclose(fichier);
    return 1;
}

int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]) {
    FILE* fichier;
    int i = 0;
    int j = 0;

    fichier = fopen(DATA_LVL, "w+");

    if (fichier == NULL)
        return 0;

    fseek(fichier, (NB_BLOCS_HAUTEUR * NB_BLOCS_LARGEUR + 2) * lvl, SEEK_SET);

    for (i = 0; i < NB_BLOCS_LARGEUR; i++) {
        for (j = 0; j < NB_BLOCS_HAUTEUR; j++) {
            fprintf(fichier, "%d", niveau[j][i]);
        }
    }
    fputc('\n', fichier);

    fclose(fichier);
    return 1;
}

void modifLvl(int mode) {
    switch (mode) {
        case 1:
            lvl++;
            break;
        case 2:
            lvl--;
            if (lvl <= 0)
                lvl = 0;
            break;
    }
}
