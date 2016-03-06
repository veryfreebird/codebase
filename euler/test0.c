#include <stdio.h>
#include <string.h>
#include "misc.h"
#undef MAX_NUM
#define MAX_NUM 6

int main()
{
    char mm[MAX_NUM] = {1,2,3,4,5,6};
    char nn[MAX_NUM] = {1,2,3,4,5,6};
    unsigned long long num; 
         
    do
    {   num = cal_perm_num(MAX_NUM, nn);
        printf("%llu\n", num);
        memcpy(mm,nn,MAX_NUM);
    }while(find_next_perm(MAX_NUM, mm, nn));
   
    return 0;
}

