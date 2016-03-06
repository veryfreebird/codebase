#include <stdio.h>
#include <string.h>

#define MAX_LEN 10000

#define START 5000

void check_fraction(int n, char *values, int *len)
{
    int num = 10, i=0; 
    memset(values, 0, MAX_LEN);
    for(;;)
    {
        if(num < n)
        {
            num = num *10;
            values[i++] = 0;
        }
        else
        if(num % n == 0)
        {
            values[i] = num / n;
            *len = i + 1;
            return;
        }
        else
        {
            values[i++] = num / n;
            num = (num % n) * 10;
        }
        if(i >= MAX_LEN)
        {
            *len = MAX_LEN;
            return;
        }
    }
}

int check_repeat(char *values, char *repeat_nums)
{
    int tocheck[5], i,j;
    tocheck[0] =  values[START];
    tocheck[1] =  values[START+1];
    tocheck[2] =  values[START+2];
    tocheck[3] =  values[START+3];
    tocheck[4] =  values[START+4];

    for(i=1;i<MAX_LEN;i++)
    {
        if(values[START+i] == tocheck[0] &&
           values[START+1+i] == tocheck[1] &&
           values[START+2+i] == tocheck[2] &&
           values[START+3+i] == tocheck[3] &&
           values[START+4+i] == tocheck[4])
           {
            for(j=0;j<i;j++)
                repeat_nums[j] =values[START+j];
            printf("\n");
            return i;
           }    
    }
    return 0;

}

void printall(char *values, int len)
{
    int i;
    for(i=0;i<len;i++)
        printf("%d",values[i]);
    printf("\n");
}

int main()
{
    char values[MAX_LEN], result[MAX_LEN], repeat_nums[MAX_LEN],save_repeat[MAX_LEN];
    int i;
    int len, repeat,max_repeat = 0, max_num;
    for(i=2;i<1000;i++)
    {
        check_fraction(i,values,&len);
        if(len == MAX_LEN)
        {
            printf("check:%d\n",i);
            repeat = check_repeat(values,repeat_nums);
            if(repeat > max_repeat)
            {
                max_repeat = repeat;
                max_num = i;
                memcpy(result, values, MAX_LEN);
                memcpy(save_repeat, repeat_nums, MAX_LEN);
            }
        }
    }
    printf("1/%d=\n", max_num);
    printall(result, len);
    
    printf("\nMAX REPEAT:%d\n", max_repeat);
    printall(save_repeat, max_repeat);    
    return 0;
}