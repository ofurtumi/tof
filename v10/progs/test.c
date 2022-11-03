#include <stdio.h>

int AnyBit1(int x) {return  x != 0;}
int AnyBit0(int x) {return ~x != 0;}
int ThirdBit1(int x) {return (x>>2)%2 == 1;}

int main(int argc, char const *argv[])
{
    printf("%d", AnyBit1(6));
    printf("%d", AnyBit0(6));
    printf("%d", ThirdBit1(0b001001001));
}
