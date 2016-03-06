#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

#define MAX_RESULT 1000

char result[MAX_RESULT]={0};

#define MAX_NUM 1000

int main()
{
  int i, sumall=0;
  result[0]=1;
  for(i=0;i<MAX_NUM;i++)
  {
    mul_value(result, result, 2, MAX_RESULT);
    E_PRINTF("\n");
  }
  for(i=0;i<MAX_RESULT;i++)
  {
    printf("%d ", result[i]);
    sumall += result[i];
  }
   
  printf("\nTotal sum: %d\n", sumall);
	return 1;
	
    
}
