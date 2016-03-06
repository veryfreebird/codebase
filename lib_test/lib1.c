#include <stdio.h>

void __attribute__((constructor)) init_function(void)
{
    printf("init lib1\n");
}
void __attribute__((destructor)) finish_function(void)
{
    printf("finish lib1\n");
}
int foobar(int i)
{
    printf("printing from lib%d.so %d\n", 1, i);
    return 1;
}

