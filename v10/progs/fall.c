// #include <stdio.h>

// short int a = 22;
// short int b = 23;
// extern int main;

// void fall() {
//     printf("a : %d, b: %d\n", a, b);
//     printf("0x%x\n", main);
// }

int a;
extern int b;
int c = 4;
int d = 5;

void fall() {
    static int d;

    a = 6;
    b = 7;
    c = 8;
    d = 9;
}
