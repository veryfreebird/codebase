#include <stdio.h>
#include <math.h>
#include "misc.h"

#define MAX_NUM 6
#define MAX_NUM1 5


bool check_num(int num, int len)
{
    int i, sum=0, temp;
    temp = num;
    for(i=0;i<len;i++)
    {
        sum += pow(temp %10, MAX_NUM1);
       
        temp = temp / 10;
    }
    if(sum == num)
    {
        return TRUE;
    }
    else
        return FALSE;
}


int main()
{
    int i, j, sum = 0, num;
    for(i=2;i<pow(10,MAX_NUM);i++)
    {
        if(check_num(i, MAX_NUM))
        {
            E_PRINTF("%4d\n", i);
            sum += i;
        }

    }
    printf("\nSum: %d\n", sum);
}

