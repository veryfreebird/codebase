#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "misc.h"

#ifndef MAX_NUM
#define MAX_NUM 1000
#endif


int m[N]={0};

void init_m()
{
    int i;
    for(i=0;i<MAX_NUM;i++)
    {
        if(i==0)m[i] = 2;
        else if(i==1) m[i] =1;
        else if((i-2)%3 == 0) m[i] = ((i-2)/3+1)*2;
        else m[i] = 1;

       /* E_PRINTF("%d ", m[i]);*/
        
    }

}


void get_convergent_of_continued_fraction(int n, int *mm, int *nn)
{
    int i; int tmp[N],next[N],kk[N];
    memset(mm, 0, N*sizeof(int));
    memset(nn, 0, N*sizeof(int));
    format_long_num(1,kk);

    if(n==0)
    {
        format_long_num(m[0],mm);
        format_long_num(1,nn);
        return;
    }

    if(n==1)
    {
        format_long_num(3,mm);
        format_long_num(1,nn);
        return;
    }
        
    
    format_long_num(m[n],nn);    
    for(i=n-1;i>=0;i--)
    {
        memcpy(mm, nn, N*sizeof(int));
        format_long_num(m[i],next);
        mul_long_nums(next,nn,tmp);
        sum_long_nums(tmp,kk,nn);
        memcpy(kk, mm, N*sizeof(int));

        
    }
}


int main()
{

    int mm[N], nn[N]; 
    int target_num = 100;

    init_m();

    get_convergent_of_continued_fraction(target_num-1, mm, nn);

    printf("numerator:\n");
    output_long_num(nn);
    printf("denominator:\n");
    output_long_num(mm);

    printf("\nSum of all the digits:%d\n", sum_long_num_digits(nn));

    return 0;
}

