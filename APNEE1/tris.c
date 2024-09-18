#include <stdlib.h>
#include <stdio.h>

#define NMAX 1000000		/* peut etre modifie si necessaire */

long nb_comparaisons_tot_insertion = 0; // variable globale permettant de conserver 
                                        // le nombre de comparaisons pour le tri par insertion
long nb_comparaisons_tot_segmentation = 0; // variable globale permettant de conserver 
                                           // le nombre de comparaisons pour le tri par segmentation


/*
generation_aleatoire
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647] selon une loi uniforme.
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/

void generation_aleatoire(int t[], int n) {
  int i ;

  for (i=0 ; i<n ; i++) {
	  t[i] = rand() ;
  } ;
}

/*
generation_aleatoire_non_uniforme
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : les valeurs t[0..n-1] ont ete initialisees avec n valeurs aleatoires
           prises dans [0,2147483647].
Pre-condition : le generateur aleatoire doit avoir ete initialise avec "srand"
*/
void generation_aleatoire_non_uniforme(int t[], int n) {
  int i;
  int x = 0;

  for (i=0; i < n; i++) {
    t[i] = x;
    x = x + ((rand() % 10) - 2);
  }
}

/*
tri_insertion
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_insertion(int t[], int n) {
  int i,j;
  int Clef;
  int nb_comparaisons = 1;
  for(i=1; i < n; i++) {
    
    Clef = t[i];
    
    j = i - 1;
    
    /* Decalage des valeurs du tableau */
    while((j >= 0) && (t[j] > Clef)) {
      t[j+1] = t[j];
      j = j - 1;
      nb_comparaisons++;
    }
    
    /* insertion de la clef */
    t[j+1] = Clef;
  }
  nb_comparaisons_tot_insertion += nb_comparaisons;
  // printf("Nombre de comparaisons tri insertion : %d\n", nb_comparaisons);
  // printf("%d\n", nb_comparaisons_tot_insertion);
}

/*
echange
Donnees : t : tableau d'entiers, k et e des indices du tableau
Resultat : le tableau t avec les éléments aux indices k et e échangés
*/
void echange(int t[], int k, int e) {
  int tmp = t[k];
  t[k] = t[e];
  t[e] = tmp;
}

/*
partition
Donnees : t : tableau d'entiers de taille > g-d, g >= 0, d < n, g < d
Resultat : la partie tableau t entre les bornes g et d est triee en ordre croissant
*/
int partition(int t[], int g, int d){
  int p = t[g];
  int k = g+1;
  int e = d;
  int nb_comparaisons = 1;
  while (e - k + 1 > 0) {
    if (t[k] <= p) {
      nb_comparaisons++;
      k++;
    }
    else {
      echange(t, k, e);
      e--;
    }
  }
  echange(t, e, g);
  nb_comparaisons_tot_segmentation += nb_comparaisons;
  return k-1;
}

/*
tri_segmentation_rec
Donnees : t : tableau d'entiers de taille > g-d, g >= 0, d < n, g < d
Resultat : le tableau t est trie en ordre croissant
*/
void tri_segmentation_rec(int t[], int g, int d) {
  if (d - g > 0) {
    int p = partition(t, g, d);
    tri_segmentation_rec(t, g, p-1);
    tri_segmentation_rec(t, p+1, d);
  }
}

/*
tri_segmentation
Donnees : t : tableau d'entiers de taille > n, n : entier > 0
Resultat : le tableau t est trie en ordre croissant
*/
void tri_segmentation(int t[], int n) {
  tri_segmentation_rec(t, 0, n-1);
}

void lancer_mesures() {

  unsigned int germe ;
  int T[NMAX];
  int N;
  int X;

  scanf("%d", &germe) ;  // Valeur du germe pour la fonction de tirage aleatoire
  srand(germe) ;
  do {
  	scanf("%d", &X) ; // Valeur de X
  } while (X<1 || X > NMAX) ;

  scanf("%d", &N) ; // Valeur de N

  while (N>=1 && N <= NMAX) { // Le programme s'arrête lorsque l'on donne un N négatif ou supérieur à NMAX
    nb_comparaisons_tot_insertion = 0;
    nb_comparaisons_tot_segmentation = 0;
    
    for (int i = 0; i < X; i++) {
      generation_aleatoire_non_uniforme(T, N) ; /* initialisation du tableau T */
      // commenter en fonction du type de tri testé
      // tri_insertion(T, N) ;	/* tri de T par insertion */ 
      tri_segmentation(T, N) ;	/* tri de T par segmentation */
    }
    
    // commenter en fonction du type de tri testé
    // printf("%d %f\n", N, (float) nb_comparaisons_tot_insertion / X);
    printf("%d %f\n", N, (float) nb_comparaisons_tot_segmentation / X);
    scanf("%d", &N) ; // Nouveau N
  } 
}
