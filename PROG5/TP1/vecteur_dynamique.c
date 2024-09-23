#include "vecteur_dynamique.h"
#include <stdlib.h>
#include <math.h>
#include <assert.h>

vecteur allouer_vecteur(int taille)
{
    assert(taille >= 0);

    vecteur v = (vecteur)malloc(sizeof(*v));

    if (v == NULL) {
        return NULL;
    }

    v->taille = taille;
    v->capacite = taille;
    v->donnees = malloc(taille * sizeof(double));
    if (v->donnees == NULL)
    {
        v->taille = -1;
    }
    return v;
}

void liberer_vecteur(vecteur v)
{
    free(v->donnees);
    free(v);
}

int est_vecteur_invalide(vecteur v)
{
    int resultat = v->taille == -1;
    return resultat;
}

double *acces_vecteur(vecteur v, int i)
{
    if (i >= 0)
    {
        if (i >= v->capacite)
        {
            if (v->donnees == NULL) {
                // v->donnees = malloc((i + 1) * sizeof(double));
                return NULL;
            } else {

                double* t;

                if (NULL != (t = realloc(v->donnees,  (i + 1) * sizeof(double)))) {
                    v->donnees = t;
                } else {
                    return NULL;
                }
                
            }
            
            v->capacite = i + 1;
            v->taille = i + 1;
        }
        return &v->donnees[i];
    }
    return NULL;
}

int taille_vecteur(vecteur v)
{
    return v->taille;
}
