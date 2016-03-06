#include <arpa/inet.h>
#include <stdio.h>

int main()
{
    int a = 16, b;
    b = htons (a);
    printf("%x:%x\n", a, b);
    return 0;
}
