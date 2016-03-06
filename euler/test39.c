#include <stdio.h>
#include "misc.h"

#define MAX_NUM 1000

bool check_num(int a, int b, int p)
{
    if(p*p == 2*a*p + 2*b*p - 2*a*b)
        return TRUE;
    else
        return FALSE;
}

int main()
{

    int i, j, k,sum=0, cnt=0, max=0, max_num;
    for(i=1;i<MAX_NUM;i++)
    {
        cnt = 0;
        /*printf("%d:\n", i);*/
        for(j=1;j<i/2;j++)
            for(k=i-1;k>=j;k--)
                if(check_num(j,k,i))
                {
                    /*printf("  %d %d %d %d\n",j,k,i-j-k,i);*/
                    cnt++;
                }
        if(cnt > max) {max = cnt; max_num = i;}
    }
    printf("max cnt: %d, max num: %d\n", max, max_num);

    return 0;
}

