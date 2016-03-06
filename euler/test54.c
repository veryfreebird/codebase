#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "misc.h"

void sort_hand(char *hand)
{
    int i,l,tmp1,tmp2;
    for(i=0;i<=3;i++)
        for(l=i+1;l<=4;l++)
            if(hand[i*2] > hand[l*2])
            {
                tmp1 = hand[i*2];
                tmp2 = hand[i*2+1];
                
                hand[i*2] = hand[l*2];
                hand[i*2+1] = hand[l*2+1];
                
                hand[l*2] = tmp1;
                hand[l*2+1] = tmp2;                
            }
}


void show_hand(char *hand)
{
    int i;
    for(i=0;i<5;i++)
        printf("%02d%c ",hand[i*2], hand[i*2+1]);
    printf("\n");
}


bool is_flush(char *hand, char *values)
{
    memset(values, 0, 5);
    
    if(hand[1] == hand[3] &&
       hand[3] == hand[5] &&
       hand[5] == hand[7] &&
       hand[7] == hand[9])
    {
       values[0] = hand[8];
       values[1] = hand[6];
       values[2] = hand[4];
       values[3] = hand[2];
       values[4] = hand[0];    
       return TRUE;
    }
    else
       return FALSE;
}

bool is_straight(char *hand,char *values)
{
    memset(values, 0, 5);

    if(hand[0]+1 == hand[2] &&
       hand[2]+1 == hand[4] &&
       hand[4]+1 == hand[6] &&
       hand[6]+1 == hand[8])
    {
        values[0] = hand[8];
       return TRUE;
    }
    else
       return FALSE;
}


bool is_straight_flush(char *hand,char *values)
{

    if(is_straight(hand, values) &&
       is_flush(hand, values))
    {
        memset(values, 0, 5);    
        values[0] = hand[8];
       return TRUE;
    }
    else
       return FALSE;
}

bool is_royal_flush(char *hand, char *values)
{
    
    if(hand[0] == 10 &&
       is_straight_flush(hand,values))
       return TRUE;
    else
       return FALSE;
}


bool is_four_of_a_kind(char *hand,char *values)
{
    memset(values, 0, 5);
    if(hand[0] == hand[4] &&
       hand[2] == hand[4] &&
       hand[6] == hand[4])
    {
       values[0] = hand[4];
       values[1] = hand[8];
       return TRUE;
    
    }  
  
    if(hand[2] == hand[4] &&
       hand[6] == hand[4] &&
       hand[8] == hand[4])
    {
       values[0] = hand[4];
       values[1] = hand[0];
       return TRUE;
    }
    return FALSE;
}
bool is_three_of_a_kind(char *hand,char *values)
{
    memset(values, 0, 5);

    if(hand[0] == hand[4] &&
       hand[2] == hand[4])
    {
       values[0] = hand[4];
       values[1] = hand[8];
       return TRUE;
    
    }
    if(hand[2] == hand[4] &&
       hand[4] == hand[6])
    {
       values[0] = hand[4];
       values[1] = hand[8];
       return TRUE;
    }

    if(hand[4] == hand[6] &&
       hand[6] == hand[8])
    {
       values[0] = hand[8];
       values[1] = hand[2];
       return TRUE;
    }

    return FALSE;
}

bool is_two_pairs(char *hand,char *values)
{
    memset(values, 0, 5);

    if((hand[0] == hand[2] &&
        hand[4] == hand[6]))
    {
        values[0] = hand[4];
        values[1] = hand[2];
        values[2] = hand[8];
        return TRUE;
    }
    if((hand[0] == hand[2] &&
        hand[6] == hand[8]))
    {
        values[0] = hand[8];
        values[1] = hand[2];
        values[2] = hand[4];
        return TRUE;
    }
    if((hand[2] == hand[4] &&
        hand[6] == hand[8]))
    {
        values[0] = hand[8];
        values[1] = hand[4];
        values[2] = hand[0];
        return TRUE;
    }

    return FALSE;
}

bool is_one_pair(char *hand,char *values)
{
    memset(values, 0, 5);

    if(hand[0] == hand[2])
    {
        values[0] = hand[2];
        values[1] = hand[8];
        return TRUE;
    }

    if(hand[2] == hand[4])
    {
        values[0] = hand[2];
        values[1] = hand[8];
        return TRUE;
    }

    if(hand[4] == hand[6])
    {
        values[0] = hand[4];
        values[1] = hand[8];
        return TRUE;
    }
    if(hand[6] == hand[8])
    {
        values[0] = hand[8];
        values[1] = hand[4];
        return TRUE;
    }
    return FALSE;
}



bool is_full_house(char *hand,char *values)
{
    memset(values, 0, 5);

    if(hand[0] == hand[2] &&
       hand[2] == hand[4] &&
       hand[6] == hand[8])
    {
        values[0] = hand[0];
        values[1] = hand[6];
        return TRUE;
    }

    if(hand[0] == hand[2] &&
       hand[4] == hand[6] &&
       hand[6] == hand[8])
    {
        values[0] = hand[8];
        values[1] = hand[0];
        return TRUE;
    }
    
    return FALSE;
}

int check_hand(char *hand, char *values)
{
    if(is_royal_flush(hand,values))
        return 10;
    if(is_straight_flush(hand, values))
        return 9;
    if(is_four_of_a_kind(hand, values))
        return 8;
    if(is_full_house(hand, values))
        return 7;
    if(is_flush(hand, values))
        return 6;
    if(is_straight(hand, values))
        return 5;
    if(is_three_of_a_kind(hand, values))
        return 4;
    if(is_two_pairs(hand, values))
        return 3;
    if(is_one_pair(hand, values))
        return 2;

    values[0] = hand[8];
    values[1] = hand[6];
    values[2] = hand[4];
    values[3] = hand[2];
    values[4] = hand[0];
    return 1;

}


char hands[1000*20] = {0};

int cnt = 0;


int main()
{
    FILE *stream; int ch; int n,cnt=0;
    char values1[5],values2[5];
    char one_hand[20];
    int result1, result2;
    
    stream = fopen("./files/poker.txt","r");
    if(stream == NULL)
    {
        printf("file open error\n");
        return 0;
    }
    fseek(stream, 0, SEEK_SET);
    n = 0;
    do {
      ch = fgetc (stream);
      if (ch != 0x20 && ch != 34 && ch != 0xD && ch != 0xA && ch != EOF)
      {
        if(n>=1000*20)
        {
            printf("no enough space to save\n");
            exit(-1);
        }
        if(ch == 'T')
            ch = 10;
        else if(ch >= '2' && ch <= '9')
            ch = ch - '0' ;
        else if(ch == 'J')
            ch = 11;
        else if(ch == 'Q')
            ch = 12;
        else if(ch == 'K')
            ch = 13;
        else if(ch == 'A')
            ch = 14;        
        
        hands[n++] = (char)ch;
      }
 
    } while (ch != EOF);
#if 1
    for(n=0;n<MAX_NUM;n++)
    {
        memcpy(one_hand, &hands[n*20], 20);

        sort_hand(one_hand);
        result1 = check_hand(one_hand,values1);
        

        sort_hand(&one_hand[10]);
        result2 = check_hand(&one_hand[10],values2);

        if(result1 > result2 || ((result1 == result2) && memcmp(values1,values2,5)> 0 ))
        {
            cnt++;
            printf("hand %d:\n", n);
            show_hand(one_hand);
            printf("player1: %d, %d %d %d %d %d\n",result1, values1[0],values1[1],values1[2],values1[3],values1[4]);        
            show_hand(&one_hand[10]);
            printf("player2: %d, %d %d %d %d %d\n\n",result2, values2[0],values2[1],values2[2],values2[3],values2[4]);

        }
        
    }
#endif  

    printf("Total hands %d wins for people1\n", cnt);
    fclose(stream);
    return 1;
}
