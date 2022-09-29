#include <stdio.h>
#include <stdlib.h>

int test(int edi)
{
    int eax = edi * 8;
    eax -= edi;
    int edx = 12 + edi * 2;
    return eax - edx;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("vantar tölu!");
        return 0;
    } else {
        printf("%i",test(atoi(argv[1])));
    }
}