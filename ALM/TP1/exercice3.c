#include <stdio.h>
#include <stdint.h>

// renvoie la valeur (0 ou 1) du bit numéro
// k dans l'entier 16 bits x
int consulte_bit(uint16_t x, unsigned int k) {
    uint16_t m = 1 << k;
    return (x & m )!= 0;
}

void modifie_bit(uint16_t *x, unsigned int k, int v) {
    uint16_t m = 1 << k;
    *x = (*x & ~m) | v << k;
}

int main()
{
    uint16_t p;
    p = 37797;
    int a = consulte_bit(p, 9);
    int b = consulte_bit(p, 10);
    modifie_bit(&p, 9, 0);
    a = consulte_bit(p, 9);
    modifie_bit(&p, 10, 1);
    b = consulte_bit(p, 10);
}