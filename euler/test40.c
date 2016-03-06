#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <string.h>
#include "misc.h"

#define MAX_NUM 1000010
char *buf;
int len=0;

int return_num(int i)
{
    int result = buf[i-1];
    printf("%d\n",result);
    return result;
}

bool save_num(int i)
{
    int num_len = check_length(i);
    int j, m=0, num = i, base;
    for(j=num_len-1;j>=0;j--)
    {
        base = pow(10, j);
        buf[len++] = num / base;
        num = num % base;
        if(len > MAX_NUM-1)
            return FALSE; 
    }
    return TRUE;
}

void printall()
{
    int i;
    for(i=0;i<MAX_NUM;i++)
    {
        printf("%d",buf[i]);
    }
    printf("\n");
}

int main()
{
    char str[20]; 
    int i;
    if((buf=malloc(MAX_NUM)) == NULL)
        return -1;
    memset(buf, 0, MAX_NUM);
    for(i=1;;i++)
    {
        if(!save_num(i))
            break;
    }
    /*printall();*/
    printf("%d\n",return_num(1)*return_num(10)*return_num(100)*return_num(1000)*return_num(10000)*return_num(100000)*return_num(1000000));
   
    free(buf);   
    return 0;
}