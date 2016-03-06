#include <stdio.h>
#include "misc.h"



bool is_pandigital_num(int num)
{
    char mark[9] = {0}; int n,j;
    if(check_length(num) !=9) return FALSE;
    
    j = num;
    for(;;)
    {
        if(j==0)break;
        else
        {
            n = j %10;
            if(n == 0 || mark[n-1] == 1)
                return FALSE;
            else
               mark[n-1] = 1;
            j = j / 10;
            
        }
    }
    return TRUE;
    
}

int main()
{

    int num, i,j,k, temp,max_num = 0;

    for(i=2;i<=9;i++)
    {
        printf("%d\n", i);
        for(k=2;k<pow(10, 9/i+1);k++)
        {
            num = 0;
            for(j=1;j<=i;j++)
            {
                temp = k*j;
                num = cat_int_num(num, temp);
            }
            if(is_pandigital_num(num))
            {
                printf("%d, %d -> %d\n", i, k, num);
                if(num > max_num) max_num = num;
            }
            if(num > 987654321)
                break;
        }
        
    }

    printf("max: %d\n", max_num);
    return 0;
}

