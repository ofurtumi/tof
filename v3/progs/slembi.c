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
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(0));

    int n = 500, k = 4;
    if (argc > 2)
    {
        n = atoi(argv[1]);
        k = atoi(argv[2]);
    }

    int *a = (int *)calloc(n, sizeof(int));
    for (int i = 0; i < k * n; i++)
    {
        int r = rand() % n;
        a[r]++;
    }

    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i] == 0)
            cnt++;
    }
    free(a);

    printf("Eftir %i ítranir eru %i hólf ennþá 0, eða %.1f%%",
           (int)k * n, cnt, ((double)cnt / (double)n) * 100);
}