#include <stdio.h>

typedef struct
{
    int a[8];
    double d;
} struct_t;

double fun(int i) {
    volatile struct_t s;
    s.d = 3.14;
    s.a[i] = 1073741824;
    return s.d;
}

int main() {
    double out = fun(2);
    printf("%f", out);
}