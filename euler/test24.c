#include <stdio.h>

#include "misc.h"


#define MAX_NUM 10

#define TEST_NUM 1000000

int num[MAX_NUM]={0};

int cnt=0;


int main()
{
    int i[MAX_NUM];

    for(i[0]=0;i[0]<MAX_NUM;i[0]++)
    {
        num[0] = i[0];
        for(i[1]=0;i[1]<MAX_NUM;i[1]++)
        {
                if(i[1] !=num[0])
                {
                    num[1] = i[1];
                    for(i[2]=0;i[2]<MAX_NUM;i[2]++)
                    {
                        if(i[2] !=num[0] && i[2] !=num[1])
                        {
                            num[2] = i[2];
                            for(i[3]=0;i[3]<MAX_NUM;i[3]++)
                            {
                                if(i[3] !=num[0] && i[3] !=num[1] && i[3] !=num[2])
                                {
                                    num[3] = i[3];
                                    for(i[4]=0;i[4]<MAX_NUM;i[4]++)
                                    {
                                        if(i[4] !=num[0] && i[4] !=num[1] && i[4] !=num[2] && i[4] !=num[3])
                                        {
                                            num[4] = i[4];
                                            for(i[5]=0;i[5]<MAX_NUM;i[5]++)
                                            {
                                                if(i[5] !=num[0] && i[5] !=num[1] && i[5] !=num[2] && i[5] !=num[3]  && i[5] !=num[4])
                                                {
                                                    num[5] = i[5];
                                                    for(i[6]=0;i[6]<MAX_NUM;i[6]++)
                                                    {
                                                        if(i[6] !=num[0] && i[6]!=num[1] && i[6] !=num[2] && i[6] !=num[3]  && i[6] !=num[4] && i[6] !=num[5])
                                                        {
                                                            num[6] = i[6];
                                                            for(i[7]=0;i[7]<MAX_NUM;i[7]++)
                                                            {
                                                                if(i[7] !=num[0] && i[7]!=num[1] && i[7] !=num[2] && i[7] !=num[3]  && i[7] !=num[4]
                                                                    && i[7] !=num[5] && i[7] !=num[5] && i[7] !=num[6])
                                                                {
                                                                    num[7] = i[7];
                                                                    for(i[8]=0;i[8]<MAX_NUM;i[8]++)
                                                                    {
                                                                        if(i[8] !=num[0] && i[8]!=num[1] && i[8] !=num[2] && i[8] !=num[3]  && i[8] !=num[4]
                                                                            && i[8] !=num[5] && i[8] !=num[5] && i[8] !=num[6] && i[8] !=num[7])
                                                                        {
                                                                            num[8] = i[8];
                                                                            for(i[9]=0;i[9]<MAX_NUM;i[9]++)
                                                                            {
                                                                                if(i[9] !=num[0] && i[9]!=num[1] && i[9] !=num[2] && i[9] !=num[3]  && i[9] !=num[4]
                                                                                    && i[9] !=num[5] && i[9] !=num[5] && i[9] !=num[6] && i[9] !=num[7] && i[9] !=num[8])
                                                                                {
                                                                                    num[9] = i[9];
                                                                                    cnt++;
                                                                                    if(cnt == TEST_NUM)
                                                                                    {
                                                                                        printf("%7d: %d%d%d%d%d%d%d%d%d%d\n", cnt, num[0], num[1], num[2], num[3], num[4], num[5],
                                                                                            num[6], num[7], num[8], num[9]);
                                                                                        return 1;;
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
                }
        }
    }
    
    return 0;
}
