#include <stdio.h>
#include <math.h>

long hoho(long rdi)
{
    long rax = rdi + 31;
    if (rdi >= 0) rax = rdi;
    rax >>= 5;        
    return rax;
}

long hoho2(long x) {
    return x/32;
}

int main()
{
    printf("%ld\n", hoho2(2048));
    printf("%ld\n", hoho2(-64));
    printf("%ld\n", hoho2(31));
    printf("%ld\n", hoho2(32));
}