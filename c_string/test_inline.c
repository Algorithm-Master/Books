#include <stdio.h>
#include <time.h>
#include <stdlib.h>

inline int static add(int a,int b)
{
    return a+b;
}

int main()
{
    srand(time(NULL));
    int x = rand() % 5;
    int y = rand() % 10;
    int u = add(x, y);
    printf("u = %d\n", u);
}
