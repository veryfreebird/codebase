#include <stdio.h>

#include "misc.h"


#define MAX_NUM 9

#define TEST_NUM 1000000

int num[MAX_NUM]={0};

int cnt=0;
int find_nums[20]={0};
void check_num(int *num)
{
    int i,j,m,n,a,b,c,k;
    for(i=1;i<MAX_NUM-2;i++)
        for(j=1;j<MAX_NUM-i;j++)
        {
            a = 0; b = 0; c = 0;
            for(m=0;m<i;m++)
            {
               a = a * 10 + num[m]; 
            }
            for(n=i;n<i+j;n++)
            {   
               b = b * 10 + num[n];
            }
            for(n=i+j;n<MAX_NUM;n++)
            {
               c = c * 10 + num[n];
            } 

            if(a*b==c)
            {
                E_PRINTF("%d %d %d\n",a, b, c);  
                for(k=0;k<20;k++)
                {
                   if(find_nums[k]==c)
                     break;
                   if(find_nums[k]==0)
                   {
                     find_nums[k]=c;
                     break;
                   }
                }                             
            }    
        }
}

int main()
{
    int i[MAX_NUM]={0};
    int k,sum=0;

    for(i[0]=1;i[0]<=MAX_NUM;i[0]++)
    {
        num[0] = i[0];
        for(i[1]=1;i[1]<=MAX_NUM;i[1]++)
        {
                if(i[1] !=num[0])
                {
                    num[1] = i[1];
                    for(i[2]=1;i[2]<=MAX_NUM;i[2]++)
                    {
                        if(i[2] !=num[0] && i[2] !=num[1])
                        {
                            num[2] = i[2];
                            for(i[3]=1;i[3]<=MAX_NUM;i[3]++)
                            {
                                if(i[3] !=num[0] && i[3] !=num[1] && i[3] !=num[2])
                                {
                                    num[3] = i[3];
                                    for(i[4]=1;i[4]<=MAX_NUM;i[4]++)
                                    {
                                        if(i[4] !=num[0] && i[4] !=num[1] && i[4] !=num[2] && i[4] !=num[3])
                                        {
                                            num[4] = i[4];
                                            for(i[5]=1;i[5]<=MAX_NUM;i[5]++)
                                            {
                                                if(i[5] !=num[0] && i[5] !=num[1] && i[5] !=num[2] && i[5] !=num[3]  && i[5] !=num[4])
                                                {
                                                    num[5] = i[5];
                                                    for(i[6]=1;i[6]<=MAX_NUM;i[6]++)
                                                    {
                                                        if(i[6] !=num[0] && i[6]!=num[1] && i[6] !=num[2] && i[6] !=num[3]  && i[6] !=num[4] && i[6] !=num[5])
                                                        {
                                                            num[6] = i[6];
                                                            for(i[7]=1;i[7]<=MAX_NUM;i[7]++)
                                                            {
                                                                if(i[7] !=num[0] && i[7]!=num[1] && i[7] !=num[2] && i[7] !=num[3]  && i[7] !=num[4]
                                                                    && i[7] !=num[5] && i[7] !=num[5] && i[7] !=num[6])
                                                                {
                                                                    num[7] = i[7];
                                                                    for(i[8]=1;i[8]<=MAX_NUM;i[8]++)
                                                                    {
                                                                        if(i[8] !=num[0] && i[8]!=num[1] && i[8] !=num[2] && i[8] !=num[3]  && i[8] !=num[4]
                                                                            && i[8] !=num[5] && i[8] !=num[5] && i[8] !=num[6] && i[8] !=num[7])
                                                                        {
                                                                            num[8] = i[8];
                                                                            cnt ++;
                                                                            check_num(num);                                                                            
                                                                           /* printf("%7d: %d%d%d%d%d%d%d%d%d\n", cnt, num[0], num[1], num[2], num[3], num[4], num[5],
                                                                                num[6], num[7], num[8]);  */
    
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
                            }
                        }
                    }
                }
        }
    }

    for(k=0;k<20 && find_nums[k]!=0;k++)
    {
       printf("%d\n",find_nums[k]);
       sum += find_nums[k];
    }        
    printf("Sum: %d\n", sum);
    return 0;
}

