#include <stdio.h>
#include <math.h>
#include "misc.h"

#define MAX_NUM 200

int samples[] ={1, 2, 5, 10, 20, 50, 100, 200};
int sums[7];

int main()
{
    int loop[8] = {0}, i, sum, cnt=0;
    
    E_PRINTF("%3d %3d %3d %3d %3d %3d %3d %3d \n", samples[0],samples[1],samples[2],samples[3],samples[4],samples[5],samples[6],samples[7]);
    for(loop[7]=0;loop[7]<MAX_NUM/samples[7]+1;loop[7]++)
    {
        sums[7] = loop[7]*samples[7];
        for(loop[6]=0;loop[6]<(MAX_NUM-sums[7])/samples[6]+1;loop[6]++)
        {
            sums[6] =sums[7]+ loop[6]*samples[6];
            for(loop[5]=0;loop[5]<(MAX_NUM-sums[6])/samples[5]+1;loop[5]++)
            {
                sums[5] = sums[6]+ loop[5]*samples[5];
                for(loop[4]=0;loop[4]<(MAX_NUM-sums[5])/samples[4]+1;loop[4]++)
                {
                    sums[4] =sums[5] + loop[4]*samples[4];
                    for(loop[3]=0;loop[3]<(MAX_NUM-sums[4])/samples[3]+1;loop[3]++)
                    {
                        sums[3]=sums[4] +  loop[3]*samples[3];
                        for(loop[2]=0;loop[2]<(MAX_NUM-sums[3])/samples[2]+1;loop[2]++)
                        {
                            sums[2] = sums[3] + loop[2]*samples[2];
                            for(loop[1]=0;loop[1]<(MAX_NUM-sums[2])/samples[1]+1;loop[1]++)
                            {
                                sums[1] = sums[2]+ loop[1]*samples[1];
                                for(loop[0]=0;loop[0]<(MAX_NUM-sums[1])/samples[0]+1;loop[0]++)  
                                {
                                    sums[0] = sums[1] + loop[0]*samples[0];
                                    if(sums[0] == MAX_NUM)
                                    {
                                        E_PRINTF("%3d %3d %3d %3d %3d %3d %3d %3d \n", loop[0],loop[1],loop[2],loop[3],loop[4],loop[5],loop[6],loop[7]);
                                        cnt ++;
                                    }
                                }
                            }
                        }
                    }                        
                }
            }
        }
    }
    printf("Total cnt: %d", cnt);            
}


