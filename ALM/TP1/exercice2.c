#include <stdio.h>
#include <stdint.h>

int main() {
    uint16_t tab[8] = {0x1234, 0x5678, 0x9ABC, 0xDEF1, 0x1FDE, 0xCBA9,
        0x8756, 0x4321};
    uint16_t *p;
    uint8_t *q;
    printf("Tailles utilisees : \
        uint16_t -> %lu, tab -> %lu, uint8_t -> %lu, uint16_t * -> %lu, \
        uint8_t * -> %lu\n",
        sizeof(uint16_t), sizeof(tab), sizeof(uint8_t), sizeof(uint16_t *),
        sizeof(uint8_t *));
    p = tab;
    q = (uint8_t *)p;
    printf("Affichage tab, parcours avec p :\n");
    for (int i = 0; i < 8; i++)
    {
        printf("tab[%d] = %x ; *(p+%d) = %x\n", i, tab[i], i, *(p + i));
    }
    printf("Affichage tab, parcours avec q :\n");
    for (int i = 0; i < 8; i++)
    {
        printf("*(q+%i) = %x\n", i, *(q + i));
    }
}