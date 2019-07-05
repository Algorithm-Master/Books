#include <stdio.h>
int static add(int a, int b)
{
    return a + b;
}

int main()
{
    int x = 5;
    int y = 10;
    int u = add(x, y);
}
