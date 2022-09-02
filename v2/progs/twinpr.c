// |||||||||||||||||||||||||||||||||
// ||    __    sjomli.is    __    ||
// ||  _/  |_ __ __  _____ |__|   ||
// ||  \   __\  |  \/     \|  |   ||
// ||   |  | |  |  /  Y Y  \  |   ||
// ||   |__| |____/|__|_|__/__|   ||
// ||                             ||
// |||||||||||||||||||||||||||||||||

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int isprime(long k)
{
    double not_top = sqrt((double)k);
    int top = (int)not_top;
    if (k <= 2)
        return 0;
    for (int i = 3; i <= top; i += 2)
    {
        if (k % i == 0)
            return 0;
    }

    return (1);
}

int main(int argc, char *argv[])
{
    // * argc segir til um fjölda argument-a
    // ? 1. argument er alltaf nafn á skránni 
    // * til að koma í veg fyrir seg-fault keyrir þetta bara ef argc > 1
    int n = argc == 2 ? atoi(argv[1]) : 10; // ! ég fokking elska ternaries
    int cnt = 0;
    int i = 3;
    int a, b;
    while (cnt < n)
    {
        if (isprime(i) && isprime(i + 2))
        {
            printf("%i og %i\n", i, i + 2);
            cnt++;
        }
        i += 2; 
    }
}