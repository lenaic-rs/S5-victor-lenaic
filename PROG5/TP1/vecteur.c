#include "vecteur.h"
#include <stdlib.h>

vecteur allouer_vecteur(int taille) {
    vecteur v = { 0, NULL }; // = (vecteur) malloc(sizeof(vecteur));
    v.taille = taille;
    v.donnees = (double *) malloc(taille*sizeof(double));
    if (v.donnees == NULL) {
        v.taille = -1;
    }
    return v;
}

void liberer_vecteur(vecteur v) {
    if (v.donnees != NULL) {
        free(v.donnees);
    }
}

int est_vecteur_invalide(vecteur v) {
    return v.taille == -1;
}

double *acces_vecteur(vecteur v, int i) {
    if (i < v.taille) {
        return &(v.donnees[i]);
    }
    return NULL;
}

int taille_vecteur(vecteur v) {
    return v.taille;
}
