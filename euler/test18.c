#include <stdio.h>
#include <math.h>
#include <string.h>
#include "misc.h"

#ifdef TEST
#define MAX_X 4
#define MAX_Y 4
char numbers[MAX_X][MAX_Y] = {
{3},
{7, 4},
{2, 4, 6},
{8, 5, 9, 3}
};
#else
#define MAX_X 15
#define MAX_Y 15
char numbers[MAX_X][MAX_Y] = {
{75},
{95, 64},
{17, 47, 82},
{18, 35, 87, 10},
{20, 04, 82, 47, 65},
{19, 01, 23, 75, 03, 34},
{88, 02, 77, 73, 07, 63, 67},
{99, 65, 04, 28, 06, 16, 70, 92},
{41, 41, 26, 56, 83, 40, 80, 70, 33},
{41, 48, 72, 33, 47, 32, 37, 16, 94, 29},
{53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14},
{70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57},
{91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48},
{63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31},
{04, 62, 98, 27, 23,   9, 70, 98, 73, 93, 38, 53, 60, 04, 23}
};
#endif
int current_max = 0;
char path[MAX_X] = {0};
char path_save[MAX_X] = {0};
int total_cnt = 0;
bool search_path(int i, int j, int current, int idx )
{
    path[idx++] = numbers[i][j];
    current += numbers[i][j];
    if(i == MAX_X-1)
    {
        total_cnt ++;
        E_PRINTF("%d  ",current);
        if(current > current_max)
        {
            current_max = current;
            memcpy(path_save, path, MAX_X);
        }
        return TRUE;
    }
    if(search_path(i+1, j, current,idx))
    {
        return search_path(i+1, j+1, current,idx);
    }
}

int main()
{
    int i,j,current=0, sum = 0;
    search_path(0,0,current,0);
    printf("\nMAX value: %d, total path cnt: %d\n", current_max, total_cnt);
    for(i=0;i<MAX_X;i++)
    {
        sum +=path_save[i];
        if(i<MAX_X-1)
            printf("%d->", path_save[i]);
        else
            printf("%d", path_save[i]);  
    } 
    printf("\nMAX value: %d\n", sum);    
    return 0;
}

