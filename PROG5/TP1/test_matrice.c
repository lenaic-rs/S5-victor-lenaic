#include "utils_tests.h"
#include <stdio.h>
#include <stdlib.h>

double *acces_matrice_verifie(matrice m, int i, int j) {
        double *element = acces_matrice(m, i, j);
        *element = 0; // Accès préalable pour vérifier que l'adresse est valide
        return element;
}

void affiche_matrice(matrice m) {
    int i, j;

    for (i = 0; i < nb_lignes_matrice(m); i++) {
        affiche_test("[ ");
        for (j = 0; j < nb_colonnes_matrice(m); j++)
            affiche_test("%g ", *acces_matrice(m, i, j));
        affiche_test("]\n");
    }
}

matrice lit_matrice(FILE *f) {
    matrice m;
    int i, j, l, c;
    fscanf(f, " %d %d", &l, &c);
    m = allouer_matrice(l, c);
    if (!est_matrice_invalide(m))
        for (i = 0; i < l; i++) {
            for (j = 0; j < c; j++)
                fscanf(f, " %lg", acces_matrice_verifie(m, i, j));
        }
    return m;
}

int teste_matrice_dynamique(matrice m) {
    int i, j;
    int extra = 10;
    int lignes, colonnes;

    lignes = nb_lignes_matrice(m);
    colonnes = nb_colonnes_matrice(m);
    for (i = -extra; i < 0; i++)
        for (j = -extra; j < colonnes + extra; j++)
            if (acces_matrice(m, i, j) != NULL) {
                affiche_test("Erreur, l'accès à un indice négatif (%d, %d) donne une adresse non nulle\n", i, j);
                return 0;
            }
    for (i = -extra; i < lignes + extra; i++)
        for (j = -extra; j < 0; j++)
            if (acces_matrice(m, i, j) != NULL) {
                affiche_test("Erreur, l'accès à un indice négatif (%d, %d) donne une adresse non nulle\n", i, j);
                return 0;
            }
    for (i = 0; i < lignes; i++)
        for (j = colonnes; j < colonnes + extra; j++)
            if (acces_matrice(m, i, j) != NULL) {
                *acces_matrice(m, i, j) = 42;
            }else {
                affiche_test("Erreur, l'accès à l'indice (%d, %d) donne une adresse nulle\n", i, j);
                return 0;
            }
    for (i = lignes; i < lignes + extra; i++)
        for (j = colonnes + extra - 1; j >= 0; j--)
            if (acces_matrice(m, i, j) != NULL) {
                *acces_matrice(m, i, j) = 42;
            }else {
                affiche_test("Erreur, l'accès à l'indice (%d, %d) donne une adresse nulle\n", i, j);
                return 0;
            }
    return 1;
}

void teste_validite(matrice *m, int n) {
    int ok=1;
#ifdef __MATRICE_DYNAMIQUE__
    if (!est_matrice_invalide(m[n])) {
        ok = teste_matrice_dynamique(m[n]);
        if (!ok)
            n++;
    }
#endif
    if (!ok || est_matrice_invalide(m[n])) {
        if (ok)
            affiche_test("Erreur d'allocation de la matrice\n");
        for (int i=0; i<n; i++)
            liberer_matrice(m[i]);
        shutdown(3);
    }
}

void test_lecture_matrice(matrice *m, int n, char *message, FILE *f) {
    m[n] = lit_matrice(f);
    teste_validite(m, n);
    affiche_test("%s :\n", message);
    affiche_matrice(m[n]);
}

int main(int argc, char *argv[]) {
    matrice m[3];
    FILE *f;

    f = ouvre_fichier_entrees("matrices", argc, argv);
    test_lecture_matrice(m, 0, "Première matrice", f);
    test_lecture_matrice(m, 1, "Seconde matrice", f);
    fclose(f);

    if (nb_colonnes_matrice(m[0]) != nb_lignes_matrice(m[1])) {
        affiche_test("Erreur, les matrices sont de taille incompatibles :\n");
        affiche_test("m[0] a %d colonnes\n", nb_colonnes_matrice(m[0]));
        affiche_test("m[1] a %d lignes\n", nb_lignes_matrice(m[1]));
        exit(4);
    }
    m[2] = allouer_matrice(nb_lignes_matrice(m[0]), nb_colonnes_matrice(m[1]));
    teste_validite(m, 2);

    for (int i=0; i<nb_lignes_matrice(m[0]); i++)
        for (int j=0; j<nb_colonnes_matrice(m[1]); j++) {
            *acces_matrice(m[2], i, j) = 0;
            for (int k=0; k<nb_colonnes_matrice(m[0]); k++)
                *acces_matrice(m[2], i, j) += *acces_matrice(m[0], i, k) * *acces_matrice(m[1], k, j);
        }
    affiche_test("Produit : \n");
    affiche_matrice(m[2]);

    liberer_matrice(m[0]);
    liberer_matrice(m[1]);
    liberer_matrice(m[2]);
    shutdown(0);
}
