#include <stdio.h>
#include <string.h>

#define MAX_LEN 200
int main(int argc, char **argv)
{
    char innstr[MAX_LEN];
    while (scanf("%s", innstr) != EOF)
    {
        if (strchr(innstr, 120) != NULL) {
            for (int i = 0; i < strlen(innstr); i++)
            {
                printf("x");
            }
        } else {
            printf("%s", innstr);
        } 
        printf("\n");
    }
    return 0;
}