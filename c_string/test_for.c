#include <stdio.h>

// 全局变量，表示递归的深度。
int depth = 0;

int f(int n) {
    ++depth；
    if (depth > 1000) throw exception;
    
    if (n == 1) return 1;
    return f(n-1) + 1;
}

/**
 *
int f(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;
    return f(n-1) + f(n-2);
}
*/
int main()
{
    int test = 0;
    test = f(7);
    printf("test value = %d \n", test);
    
    int a = 0;
    for(int i = 0; i < 3; i++)
    {
        a += i;
    }
}

