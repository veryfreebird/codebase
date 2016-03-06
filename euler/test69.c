#include <stdio.h>
#include <string.h>
#include "misc.h"


#ifndef MAX_NUM
#define MAX_NUM 6
#endif

bool is_relatively_prim(int n, int i)
{
    int j;
    if(i==1)
        return TRUE;
    if(i == 2 && n %2 ==1)
        return TRUE;
    if(check_prime_with_samples(i) && n % i !=0)
        return TRUE;
    if(i+1 == n)
        return TRUE;
    if(i+2 == n && n%2 ==1)
        return TRUE;

    
    for(j=2;j<=i;j++)
    {
        if(i % j ==0 && n % j ==0)
            return FALSE;
    }
    return TRUE;
}

double cal_value(int n)
{
    int i, cnt=0;
    if(check_prime_with_samples(n))
        for(i=1;i<n;i++)
        {
            E_PRINTF("%d ", i);
            cnt = n-1;
        }
    else
        for(i=1;i<n;i++)
        {
            if(is_relatively_prim(n,i)){E_PRINTF("%d ", i); cnt++;}
        }
    E_PRINTF("\n");
    return (double)n/(double)cnt;
}


int main()
{
    int i;
    if(!constrcut_prime_check(MAX_NUM))
        return -1;;

    for(i=2;i<=MAX_NUM;i++)
        printf("%7d:%f\n",i, cal_value(i));

    deconstruct_prime_check();
    return 0;
}

