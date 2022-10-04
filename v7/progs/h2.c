#include <stdio.h>

long whi(long k)
{
    int i = 0;
    while (k != 0)
    {
        long x = k - 1;
        k = x & k;
        i = 1 ^ i;
    }

    return i;
}

int main()
{
    printf("%ld", whi(12000));
}