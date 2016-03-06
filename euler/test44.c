#include <stdio.h>
#include <string.h>
#include "misc.h"

#define MAX_NUM 5000

int main()
{

    int pentagonal_num[MAX_NUM] = {0};
    int i,j;
    for(i=0;i<MAX_NUM;i++)
    {
        pentagonal_num[i] = cal_pentagonal_num(i+1);
        E_PRINTF("%d\n", pentagonal_num[i]);
    }

    for(i=0;i<MAX_NUM-1;i++)
        for(j=i+1;j<MAX_NUM;j++)
            if(is_pentagonal_num(pentagonal_num[j]-pentagonal_num[i]) &&
               is_pentagonal_num(pentagonal_num[j]+pentagonal_num[i]) ) 
            {
                printf("i:%d-%d, j:%d-%d, p[j]-p[i]:%d\n",i+1,pentagonal_num[i],j+1, pentagonal_num[j],pentagonal_num[j]-pentagonal_num[i]);
                return 0;
            }


    return 0;
}

