#include <stdio.h>

int foobar(int i)
{
    printf("printing from lib%d.so %d\n", 2, i);
    return 2;
}

