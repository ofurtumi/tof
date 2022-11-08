#include <stdio.h>

int main(int argc, char const *argv[])
{

    int i,j;
    char stop = 0;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            if (i == 2 && j == 3) {
                stop = 1;
                break;
            }
        }
        if (stop) break;
    }

    printf("i: %d, j: %d", i, j);
    return 0;
}
