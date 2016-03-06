#include <stdio.h>
#include <string.h>
#include "misc.h"

#ifndef MAX_NUM
#define MAX_NUM 10000
#endif

int results[MAX_NUM][N]={0};
int seq[MAX_NUM];

int sort_seq[MAX_NUM];
int sort_results[MAX_NUM][N]={0};
int cnt = 0;

/*
make -e t=62 n=20 m=10000

*/



void insert_num(int n)
{
    int i,j;
    if(cnt == 0)
    {
        memcpy(sort_results[0], results[n], N*sizeof(int));
        cnt++;
        sort_seq[0] = seq[n];
    }
    else
    {   if(compare_long_nums(sort_results[cnt-1], results[n])>0)
        {
            for(i=cnt-1;i>=0;i--)
            {
                if(compare_long_nums(sort_results[i], results[n])<0)
                {
                    for(j=cnt-1;j>i;j--)
                    {
                        memcpy(sort_results[j+1], sort_results[j], N*sizeof(int));
                        sort_seq[j+1] = sort_seq[j];                    
                    }
                    memcpy(sort_results[i+1], results[n], N*sizeof(int));
                    sort_seq[i+1] = seq[n];
                    break;     
                }
            }
        }
        else
        {
            memcpy(sort_results[cnt], results[n], N*sizeof(int));
            sort_seq[cnt] = seq[n];     
        }
        cnt++;       
    }
}

int main()
{
    long long i,n,k; 
    long long result;
    
    for(i=0;i<MAX_NUM;i++)
    {
        result = i*i*i;
        format_long_long_num(result, &results[i][0]);
        sort_list(&results[i][1],results[i][0]);
       
        printf("%lld:",i);
        output_long_num(results[i]);
     
        seq[i] = i;
        insert_num(i);
    }

    for(i=0;i<MAX_NUM;i++)
    {
#if 0    
        printf("%2d: %d",i, sort_seq[i]);    
        output_long_num(sort_results[i]);
#endif
        if(memcmp(sort_results[i],sort_results[i+1],N*sizeof(int))==0 &&
           memcmp(sort_results[i],sort_results[i+2],N*sizeof(int)) ==0 && 
           memcmp(sort_results[i],sort_results[i+3],N*sizeof(int)) ==0 &&
           memcmp(sort_results[i],sort_results[i+4],N*sizeof(int)) ==0)
           {
            printf("%d %d %d %d %d\n", sort_seq[i],sort_seq[i+1],sort_seq[i+2],
                sort_seq[i+3],sort_seq[i+4]);
            /*break;*/
           }        
    }
    
    
        
    return 0;
}

