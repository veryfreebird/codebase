#ifndef __MISC__H
#define __MISC__H

#ifdef PRINT_LOG
#define E_PRINTF printf
#else
#define E_PRINTF
#endif


#define TRUE 1
#define FALSE 0

typedef char bool;

#ifndef N
#define N 1100
#endif

#endif
