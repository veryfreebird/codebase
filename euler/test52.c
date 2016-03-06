#include <stdio.h>
#include <string.h>
#include <math.h>
#include "misc.h"

#define MAX_NUM 6
void sort_list(int *list, int len)
{
    int i,l,tmp;
    for(i=0;i<=len-2;i++)
        for(l=i+1;l<=len-1;l++)
            if(list[i] > list[l])
            {
                tmp = list[i];
                list[i] = list[l];
                list[l] = tmp;
            }
}

int main()
{
    int i, j,tmp;
    int a[N],b[N];
    for(i=10;;i++)
    {
        memset(a, 0, N*sizeof(int));
        format_long_num(i,a);
        sort_list(&a[1],a[0]);
        for(j=2;j<=MAX_NUM;j++)
        {
            tmp = i*j;
            memset(b, 0, N*sizeof(int));
            format_long_num(tmp,b);
            sort_list(&b[1],b[0]);

            if(memcmp(a,b, N*sizeof(int))!=0)
                break;
        }
        if(j==MAX_NUM+1)
        {
            printf("%d\n", i);
            break;
        }
    }
   
}


