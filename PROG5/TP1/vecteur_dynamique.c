#include "vecteur_dynamique.h"
#include <stdlib.h>

vecteur allouer_vecteur(int taille) {
    vecteur v = (vecteur) malloc(sizeof(vecteur));
    v->taille = taille;
    v->capacite = taille;
    v->donnees = malloc(taille * sizeof(double));
    if (v->donnees == NULL) {
        v->taille = -1;
    }
    return v;
}

void liberer_vecteur(vecteur v) {
    free(v->donnees);
}

int est_vecteur_invalide(vecteur v) {
    int resultat = v->taille == -1;
    return resultat;
}

double *acces_vecteur(vecteur v, int i) {
    if (i > v->capacite) {
        v->donnees = realloc(v->donnees, i * sizeof(double));
        v->capacite = i;
    }
    return &v->donnees[i];
}

int taille_vecteur(vecteur v) {
    return v->taille;
}
