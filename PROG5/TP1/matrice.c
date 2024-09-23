#include "matrice.h"
#include <stdlib.h>

matrice allouer_matrice(int l, int c) {
    matrice m = { 0, 0, NULL };
    m.l = l;
    m.c = c;
    m.donnees = malloc(l*sizeof(double *));
    int ok = m.donnees != NULL;
    int i = 0;
    for (;i < l && ok; i++) {
        m.donnees[i] = malloc(c*sizeof(double));
        ok = m.donnees[i] != NULL;
    }
    if (!ok) {
        for (int j = 0; j < i-1; j++){
            free(m.donnees[j]);
        }
        free(m.donnees);
        m.l = -1;
        m.c = -1;
    }
    return m;
}

void liberer_matrice(matrice m) {
    if (est_matrice_invalide(m)) {
        return;
    }
    for (int j = 0; j < m.l; j++){
        free(m.donnees[j]);
    }
    free(m.donnees);    
}

int est_matrice_invalide(matrice m) {
    return (m.l == -1) || (m.c == -1);
}

double *acces_matrice(matrice m, int i, int j) {
    return &m.donnees[i][j];
}

int nb_lignes_matrice(matrice m) {
    return m.l;
}

int nb_colonnes_matrice(matrice m) {
    return m.c;
}
