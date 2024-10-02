#include "matrice_dynamique.h"
#include "vecteur_dynamique.h"
#include <stdlib.h>
#include <stdio.h>

struct donnees_matrice {
    int l, c, capacite;
    vecteur *donnees;
};

/*matrice allouer_matrice(int l, int c) {
    matrice m = (matrice)malloc(sizeof(*m));

    if (m == NULL) {
        return NULL;
    }

    m->l = l;
    m->c = c;
    m->capacite = l;
    m->donnees = malloc(l*sizeof(vecteur));
    int ok = m->donnees != NULL;
    if (m->donnees == NULL) {
        m->l = -1;
        m->c = -1;
        return m;
    }
    int i = 0;
    for (; i < l && ok; i++){
        m->donnees[i] = allouer_vecteur(c);
        if (m->donnees == NULL) {
            m->l = -1;
            m->c = -1;
            return m;
        }
    }
    if (!ok) {
        for (int j = 0; j < i-1; j++){
            free(m->donnees[j]);
        }
        free(m->donnees);
        m->l = -1;
        m->c = -1;
    }
    return m;
}

void liberer_matrice(matrice m) {
    for (int i = 0; i < m->l; i++) {
        free(m->donnees[i]);
    }
    free(m->donnees);
    free(m);
}

int est_matrice_invalide(matrice m) {
    return m->l == -1;
}

double *acces_matrice(matrice m, int i, int j) {
    if ((i > 0) && (j > 0)) {
        if (i >= m->capacite) {
            double *t;
            if (NULL != (t = realloc(m->donnees, (i * 2) * sizeof(vecteur)))) {
                m->donnees = t;
            }
        }
    }
    double *resultat = acces_vecteur[m->donnees[i], j];
    return resultat;
}

int nb_lignes_matrice(matrice m) {
    int resultat = m->l;
    return resultat;
}

int nb_colonnes_matrice(matrice m) {
    int resultat = m->c;
    return resultat;
}
*/