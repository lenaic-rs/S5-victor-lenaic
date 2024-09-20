#include <stdio.h>

int main() {
    int *q;
    printf("test");
    printf("q = %d, *q = %d\n", (int )q, *q);
    int x=5,y;
    printf("&x = %d, x = %d\n", (int )&x, x);
    printf("&y = %d, y = %d\n", (int )&y, y);
    int *p = &x;
    printf("p = %d, *p = %d\n", (int )p, *p);
    printf("&x = %d, x = %d\n", (int )&x, x);
    *p = 3;
    printf("p = %d, *p = %d\n", (int )p, *p);
    printf("&x = %d, x = %d\n", (int )&x, x);
    p = &y;
    printf("p = %d, *p = %d\n", (int )p, *p);
    printf("&y = %d, y = %d\n", (int )&y, y);
    *p += 1;
    printf("p = %d, *p = %d\n", (int )p, *p);
    printf("&y = %d, y = %d\n", (int )&y, y);
}