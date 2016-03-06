#include <stdio.h>
#include <string.h>
#include "misc.h"
#undef MAX_NUM
#define MAX_NUM 6

#define MINIMUM_NUM 1000
#define MAXIMUM_NUM 9999


int cal_figurate_num(int n, int m)
{
    int num;
    switch(n)
    {
        case 3:
            num = m*(m+1)/2;
            break;
        case 4:
            num = m*m;
            break;
        case 5:
            num = m*(3*m-1)/2;
            break;
        case 6:
            num = m*(2*m-1);
            break;
        case 7:
            num = m*(5*m-3)/2;
            break;
        case 8:
            num = m*(3*m-2);
            break;
        default:
            break;
    }
    return num;
   
}

int figurates[MAX_NUM][10000]={0};
int cnts[MAX_NUM]={0};

int patterns[MAX_NUM][400]={0};
int sets[MAX_NUM][MAX_NUM]={0};
int n_sets[MAX_NUM];
int pattern_cnt[MAX_NUM];


void collect_patterns(int n, int *in_sets)
{
    int i, j;
    pattern_cnt[n] = 0;
    memset(patterns[n], 0, 400*sizeof(int));
    memcpy(sets[n], in_sets, MAX_NUM*sizeof(int));
    n_sets[n] = n;

    for(i=0;i<n;i++)
    {
        for(j=0;j<cnts[in_sets[i]];j++)
        {
            patterns[n][pattern_cnt[n]++] = figurates[in_sets[i]][j];
        }
    }

    E_PRINTF("pattern(%d):\n", pattern_cnt[n]);
    for(j=0;j<pattern_cnt[n];j++)
    {
        E_PRINTF("%d ", patterns[n][j]);
    }
    E_PRINTF("\n");
    
}

int check_set(int n, int idx)
{
    int sum =0,j;

    for(j=0;j<n;j++)
    {
        sum = sum + cnts[sets[n][j]];
        if(idx <= sum)
            return sets[n][j];
    }
    return -1;
}

int main()
{
    int i,j,k,num; int kk[MAX_NUM],tocheck[MAX_NUM],check_result[MAX_NUM];
    int setn[MAX_NUM];
    for(i=0;i<MAX_NUM;i++)
    {
        for(j=0;;j++)
        {
            num = cal_figurate_num(i+3,j);
            if(num >= MINIMUM_NUM && num <=MAXIMUM_NUM)
            {
                figurates[i][cnts[i]++]=num;
            }
            else
            if(num > MAXIMUM_NUM)
                break;
        }
    }


    
#if 1   
    memset(setn, 0, MAX_NUM*sizeof(int)); 
    setn[0] = 4; setn[1] = 3; setn[2] = 2; setn[3] = 1; setn[4] = 0; 
    collect_patterns(5, setn);
    check_result[5]=5;
    for(kk[5]=0;kk[5]<cnts[5];kk[5]++)
    {
        tocheck[5]=figurates[5][kk[5]];
        for(kk[4]=0;kk[4]<pattern_cnt[5];kk[4]++)
        {
            if(tocheck[5]%100 == patterns[5][kk[4]]/100)
            {
                check_result[4] = check_set(5,kk[4]);num=0;
                for(k=MAX_NUM-1;k>=0;k--)
                {
                    if(k!=check_result[5] && k!=check_result[4])
                        setn[num++]=k;
                }
                collect_patterns(4, setn);
                tocheck[4] = patterns[5][kk[4]];
                for(kk[3]=0;kk[3]<pattern_cnt[4];kk[3]++)
                {
                    if(tocheck[4]%100 == patterns[4][kk[3]]/100)
                    {
                        check_result[3] = check_set(4,kk[3]);num=0;
                        for(k=0;k<MAX_NUM;k++)
                        {
                            if(k!=check_result[5] && k!=check_result[4] && k!=check_result[3])
                                setn[num++]=k;
                        }
                        collect_patterns(3, setn);
                        tocheck[3] = patterns[4][kk[3]];
                        for(kk[2]=0;kk[2]<pattern_cnt[3];kk[2]++)
                        {
                            if(tocheck[3]%100 == patterns[3][kk[2]]/100)
                            {
                                check_result[2] = check_set(3,kk[2]);num=0;
                                for(k=0;k<MAX_NUM;k++)
                                {
                                    if(k!=check_result[5] && k!=check_result[4] && k!=check_result[3]
                                        && k!=check_result[2])
                                        setn[num++]=k;
                                }
                                collect_patterns(2, setn);
                                tocheck[2] = patterns[3][kk[2]];
                                for(kk[1]=0;kk[1]<pattern_cnt[2];kk[1]++)
                                {
                                    if(tocheck[2]%100 == patterns[2][kk[1]]/100)
                                    {
                                        check_result[1] = check_set(2,kk[1]);num=0;
                                        for(k=0;k<MAX_NUM;k++)
                                        {
                                            if(k!=check_result[5] && k!=check_result[4] && k!=check_result[3] && k!=check_result[2] && k!=check_result[1])
                                                setn[num++]=k;
                                        }
                                        collect_patterns(1, setn);
                                        tocheck[1] = patterns[2][kk[1]];
                                        for(kk[0]=0;kk[0]<pattern_cnt[1];kk[0]++)
                                        {
                                            check_result[0] = setn[0];
                                            if(tocheck[1]%100 == patterns[1][kk[0]]/100 && patterns[1][kk[0]]%100 == tocheck[5]/100)
                                            {
                                                tocheck[0] = patterns[1][kk[0]];
                                                printf("%d %d %d %d %d %d\n", check_result[5]+3,check_result[4]+3,check_result[3]+3,check_result[2]+3,check_result[1]+3,check_result[0]+3);
                                                printf("%d %d %d %d %d %d\n", tocheck[5],tocheck[4],tocheck[3],tocheck[2],tocheck[1],tocheck[0]);
                                                printf("sum:%d\n", tocheck[5]+tocheck[4]+tocheck[3]+tocheck[2]+tocheck[1]+tocheck[0]);
                                             }
                                        }
                                     }
                                }
                                
                             }
                        }

                        
                    }
                }

                
            }
        }
        
        
    }
#endif    
end:

#if 0
    for(i=0;i<MAX_NUM;i++)
    {
        printf("%d figurates(%d):\n", i+3,cnts[i]);
        for(j=0;j<cnts[i];j++)
        {
            printf("%d ", figurates[i][j]);
        }
        printf("\n");
        cnt = cnt + cnts[i];
    }

#endif

    return 0;
}

