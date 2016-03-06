#include <stdio.h>
#include "misc.h"


bool check_num(int a, int b)
{

    int a1, b1;
    if(a==b)return FALSE;
    if(a %10 == b / 10)
    {
        a1=a/10;
        b1=b%10;
        if(a1*b == a*b1)
            return TRUE;
    }
    if(a /10 == b %10)
    {
        a1=a%10;
        b1=b/10;
        if(a1*b == a*b1)
            return TRUE;
    } 
    return FALSE;

}


int main()
{
    int i,j;
    for(i=10;i<100;i++)
        for(j=10;j<100;j++)
            if(i<j && check_num(i,j))
                printf("%d,%d\n", i, j);

    return 0;
}

