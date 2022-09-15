#include <stdio.h>

int main() {
    short sx = -2;
    int x = -14;
    unsigned ux = sx;
    printf("sx: %d, ux: %u, MAX: %u \n" , sx, ux,__UINT32_MAX__);
    printf("x - (sx << 1): %d\n", x - (sx << 1));
    
    printf("x: %d \n", x >> 3);
    printf("less: %d\n",(x+ux)<0);
    printf("plus: %u\n",ux + sx);

    int a = -130;
    printf("%d\n", a&~(a >> 31));

    __int8_t sh1 = 250;
    __int8_t sh2 = 5;
    printf("%d",sh1+sh2);
}