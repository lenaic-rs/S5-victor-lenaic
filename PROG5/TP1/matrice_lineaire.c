#include "matrice_lineaire.h"
#include <stdlib.h>

matrice allouer_matrice(int l, int c) {
    matrice m = { 0, 0, NULL };
    m.l = l;
    m.c = c;
    m.donnees = malloc(l*c*sizeof(double));
    if (m.donnees == NULL) {
        m.l = -1;
        m.c = -1;
    }
    return m;
}

void liberer_matrice(matrice m) {
    free(m.donnees);
}

int est_matrice_invalide(matrice m) {
    return m.l == -1;
}

double *acces_matrice(matrice m, int i, int j) {
    return &m.donnees[i*m.c+j];
}

int nb_lignes_matrice(matrice m) {
    int resultat = m.l;
    return resultat;
}

int nb_colonnes_matrice(matrice m) {
    int resultat = m.c;
    return resultat;
}
