#include <stdio.h>

int func(int n)
{
    printf("%d", n);
    if (n <= 1)
        return 1;
    return (n * 3) + func(n / 4);
}

int main() {
    printf("%d",func(16));
}