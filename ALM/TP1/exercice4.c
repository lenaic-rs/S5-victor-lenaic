#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int present(int k, int *c) {
    return c[k] == 1;
}

void suppression(int k, int *c) {
    c[k] = 0;
}

void construit_crible(int *c, int n) {
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

int present(int k, int *c) {
    return c[k] == 1;
}

void suppression(int k, int *c) {
    c[k] = 0;
}

void construit_crible(int *c, int n) {
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
int *crible, x, k;
if (argc == 2) {
x = atoi(argv[1]);
crible = (int *)malloc(x*sizeof(int));
construit_crible(crible, x);
printf("Nombres premiers jusqu'a %d : \n", x);
for(k=0; k<x; k++)
if (present(k,crible)) printf("%d, ", k);
printf("\n");
}
else {
fprintf(stderr, "./crible <nombre>\n");
return 1;
}
return 0;
}