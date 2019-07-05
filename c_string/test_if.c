#include <time.h>
#include <stdio.h>

int main()
{
    srand(time(NULL));
    int r = rand() % 2;

    int a = 10;
    if(r == 0) {
        a = 1;
    } else {
        a = 2;
    }
}
