#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

int weekday = 7;
int year = 1900;
int month = 1;
int day = 1;

bool leapyear(int year)
{
    if(year%400 ==0 ||(year%100 !=0 && year%4==0))
        return TRUE;
    else
        return FALSE;
}

int days_normal[12]=
{
    31,28,31,30,31,30,31,31,30,31,30,31
};

int days_leap[12]=
{
    31,29,31,30,31,30,31,31,30,31,30,31
};

int days_of_normal = 365;
int days_of_leap     = 366;

int cal_days(int year, int month, int day)
{
    int i, days = 0; bool is_leapyear;
    for(i=1900; i<year;i++)
        if(leapyear(i))
            days +=366;
        else
            days +=365;
    is_leapyear = leapyear(year);
    for(i=0;i<month-1;i++)
        if(is_leapyear)
            days += days_leap[i];
        else
            days += days_normal[i];

    days += day;
    return days;      
}

int main()
{
    printf("%d ",cal_days(2000,1,1) % 7);

    int i, j, cnt=0;
    for(i=1901;i<2001;i++)
        for(j=1;j<13;j++)
        {
            if((cal_days(i,j,1)) % 7 ==0)
            {
                cnt++;
                printf("%d-%02d-01\n", i, j);
            }
        }
    printf("Total cnt: %d", cnt);
    
    return 0;
}


