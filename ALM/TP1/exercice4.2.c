#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int present(int k, uint32_t *c){ // l'entier k "est dans" le crible c
 
    uint16_t m = 1 << (k % 32);
    return (c[k / 32] & m) != 0;
}

void suppression(int k, uint32_t *x) {

    uint16_t m = 1 << k;
    *x = (*x & ~m) | 0 << k;
}

void construit_crible(uint32_t *c, int borne, int n) {
    // toodo
    for (int i = 0; i < n; i++) {
        c[i] = 1;
    }
    for (int k =2; k < n; k++) {
        if (present(k, c)) {
            int m = 2;
            int r = m * k;
            while (r < n) {
                suppression(r, c);
                m++;
                r = m * k;
            }
        }
    }
}

int main(int argc, char **argv) {
int x, borne;
uint32_t *crible;
if (argc == 2) {
x = atoi(argv[1]);
borne = x/32 + 1;
crible = (uint32_t *)malloc(borne*sizeof(uint32_t));
construit_crible(crible, borne, x);
printf("Nombres premiers jusqu'a %d : \n", x);
// mettre instructions pour affichage...
}
else {
fprintf(stderr, "./crible <nombre>\n");
return 1;
}
return 0;
}