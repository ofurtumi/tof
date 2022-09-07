#include <stdio.h>

int main() {
    int x = 10;
    int y = 10;
    int *p = &x;
    int *q = &y;

    printf("x: %d, p: %p, q: %p \n", x, p, q);
    printf("*p: %i, *q: %i \n", *p, *q);
    printf("p == q: %d, *p == *q: %d", p == q, *p == *q);
}