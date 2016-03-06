#include <stdio.h>
#include <string.h>
#include "misc.h"

#define MAX_NUM 1000

int aa[N]={0}; 
int bb[N]={0};

void find_next(int *m, int *n)
{
    memcpy(aa, m, N*sizeof(int));
    memcpy(bb, n, N*sizeof(int));    

    sum_long_nums(aa, bb, n);
    sum_long_nums(n, bb, m);
}

int main()
{
    int m[N]={0},n[N]={0}; int j,cnt=0;
    format_long_num(3,m);
    format_long_num(2,n);

    for(j=1;j<=MAX_NUM;j++)
    {
        E_PRINTF("%d:%lld/%lld\n",j,m,n);
        if(m[0]>n[0])
        {
            cnt++;
            printf("Found%d:\n", j);
            output_long_num(m);
            output_long_num(n);
        }
        find_next(m, n);
    }
    printf("Total count %d matched\n", cnt);   
    return 0;
}

