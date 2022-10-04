#include <stdio.h>
#include <stdlib.h>

// |||||||||||||||||||||||||||||||||
// ||    __    sjomli.is    __    ||
// ||  _/  |_ __ __  _____ |__|   ||
// ||  \   __\  |  \/     \|  |   ||
// ||   |  | |  |  /  Y Y  \  |   ||
// ||   |__| |____/|__|_|__/__|   ||
// ||                             ||
// |||||||||||||||||||||||||||||||||

int func(int n) {
    int out;
    switch (n)
    {
    // .L6
    case 0:
    case 2:
        out = 2*n+3;
        break;
    // .L5
    case 3:
    case 4:
        out = n+3;
        break;
    // .L3
    case 5:
        int temp = n*8;
        out = 3 - temp;
        break;
    // .L7
    default:
        out = n;
        break;
    }
    return out;
}

int main(int argc, char **argv) {
    if(argc > 1) printf("%d", func(atoi(argv[1])));
}