#include <stdio.h>
//test.c 
void foo1();
void foo2();
int
main (void)
{
    int i;
    for(i=0;;i++)
    {
        foo1 ();
        foo2 ();
    }
}
