#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

/*1 to 9*/
char num1[9][10]={
  "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"
}; 

/*10 to 19*/
char num2[10][10]={  
  "Ten","Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", 
  "Seventeen",  "Eighteen", "Nineteen"
};

/*20,30,40,90*/
char num3[8][10]={
  "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
};

char Hundred[20] = "Hundred";

char And[10]="And";

int convert_integer(int num, char *str)
{
  char tmp[100]="\0";
     if(num>=100)
      {
        strcat(tmp, num1[num/100-1]);
        strcat(tmp, Hundred);
      }
      if(num%100 != 0)
      {
        if(num>100)
          strcat(tmp, And);

        if(num%100 <10)
        {
            strcat(tmp, num1[num%100-1]);
        }
        else
        if(num%100 <20)
        {
            strcat(tmp, num2[num%100-10]);
        }
        else
        {         
            strcat(tmp, num3[(num%100)/10-2]);
            if(num%10 !=0)
              strcat(tmp, num1[num%10-1]);
        }
      }
  
  strcpy(str, tmp);
  return strlen(str);
}

int main()
{
  int i,cnt,sum=0;
  char number[100]="\0";
  for(i=1;i<1000;i++)
  {
    number[0]=0;
    cnt = convert_integer(i, number);
    printf("%4d: %s %d\n",i, number, cnt);
    sum +=cnt;
  }
  printf("1000: OneThousand %d\n",i, number, strlen("onethousand"));
  printf("Total: %d\n", sum+strlen("onethousand"));        
	return 1;
	
    
}

