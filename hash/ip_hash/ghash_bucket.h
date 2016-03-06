#ifndef _APP_GHASH_BUCKET_H__
#define  _APP_GHASH_BUCKET_H__

#include "jhash.h"
#include "dlist.h"



struct ghash_bucket__t;
typedef struct ghash_bucket__t  ghash_bucket__t;
typedef struct ghash_bucket_stat__t
{
   int min, max;
   int distribution[5];  /*0:   <= 4
                           1:   <=8
                           2:   <=16
                           3:   <=32
                           4:   >32
                         */
}ghash_bucket_stat__t;
typedef  void *      GHASH_KEY;
typedef  int         (*GHASH_EQUAL_F)(dlist_t *head,GHASH_KEY key);
typedef  u32         (*GHASH_KEY_F)(GHASH_KEY  key,u32 rand_value);
typedef  void *      (*GHASH_TRAVERSE_NODE_F)(dlist_t *head,void *buffer);

ghash_bucket__t *ghash_bucket_create__r(int buck_size,GHASH_EQUAL_F cmp_f,GHASH_KEY_F key_f,u32 rand_value);
dlist_t         *ghash_bucket_search__r(ghash_bucket__t *hash_bucket,GHASH_KEY key);
void             ghash_bucket_insert__r(ghash_bucket__t *hash_bucket,dlist_t *node, GHASH_KEY key);
void             ghash_bucket_delete__r(ghash_bucket__t *hash_bucket,dlist_t *node, GHASH_KEY key);
void             ghash_bucket_destroy__r(ghash_bucket__t *hash_bucket);
void             ghash_bucket_stat__r(ghash_bucket__t *hash_bucket,ghash_bucket_stat__t *ghash_bucket_stat);
int   g_hash_bucket_traverse__r(ghash_bucket__t *hash_bucket,GHASH_KEY key,GHASH_TRAVERSE_NODE_F trav_f,void * buffer,int max_item);

#endif
