#ifndef APP_JHASH_H__
#define APP_JHASH_H__

typedef unsigned int   u32;
typedef unsigned char u8;

u32 jhash(void *key, u32 length, u32 initval);

#endif
