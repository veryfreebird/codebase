#include <stdio.h>
#include <math.h>
#include <string.h>

#include "misc.h"

bool is_triangle_num(int num)
{
    int m;
    m = sqrt(1+8*num);

    if(m>=3 && (m %2 == 1) && (m*m == (1+8*num)))
        return TRUE;
    else
        return FALSE;
}

int main()
{
    FILE *stream; int ch; int n, cnt=0;
    char tmp[20],tmp1; int sum=0;
    stream = fopen("./files/words.txt","r");
    if(stream == NULL)
    {
        printf("file open error\n");
        return 0;
    }
    fseek(stream, 0, SEEK_SET);
    n = 0;
    tmp[0]='\0';
    
    do {
      ch = fgetc (stream);
      if (ch== 44 || ch== EOF)
      {
        tmp[n]='\0'; 
        printf("%s - %d\n", tmp, sum);
        if(is_triangle_num(sum))  
            cnt++;
        
        n=0;
        tmp[0]='\0';
        sum = 0;
      }
      else if (ch != 34)
      {
        tmp[n++] = (char)ch;
        sum += ch - 'A' + 1;
      }
 
    } while (ch != EOF);

    printf("Total cnt: %d\n", cnt);

    fclose(stream);
    return 1;
}

