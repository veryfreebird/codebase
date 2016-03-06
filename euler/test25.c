#include <stdio.h>
#include <math.h>
#include <string.h>

#include "misc.h"

int n1[N], n2[N], n3[N];
int main()
{
    int i;
    n1[0]=1;n1[1]=1;
    n2[0]=1;n2[1]=1;

    for(i=3;;i++)
    {
        sum_long_nums(n1,n2,n3);
        if(n3[0] == 1000) {printf("\nThe %dth num\n",i);break;}
        memcpy(n1, n2, N*sizeof(int));
        memcpy(n2, n3, N*sizeof(int));
    }
}

