/********************************************************************************
 *Function: Module for a general hash bucket imeplementation
 *         1.  All the elements that hash collide are linked by a double cyclical list.
 *         2.  The elements should contain a field with type dlist_t
 *         3.  Do not care about the memory management.
 ********************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ghash_bucket.h"

#define GHASH_BUCK_STAT

typedef struct
{
   dlist_t     head;
   u32         count;
}ghash_bucket_head__t;

struct ghash_bucket__t
{
  u32                         buck_size;
  ghash_bucket_head__t       *bucket;
  GHASH_EQUAL_F               cmp_f;
  GHASH_KEY_F                 key_f;
  u32                         rand_value;
#ifdef GHASH_BUCK_STAT
  int                         max, min; 
#endif
};

/*Function: Create a hash bucket table
  Parameter: 
           buck_size      the size of bucket
           cmp_f          function pointer to equal 
           key_f          function pointer to get hash table index
           rand_value     a parameters for key_f 
*/
ghash_bucket__t *ghash_bucket_create__r(int buck_size,GHASH_EQUAL_F cmp_f,GHASH_KEY_F key_f,u32 rand_value)
{
  ghash_bucket__t *hash;
  int  i;

  hash= ( ghash_bucket__t *)malloc(sizeof(ghash_bucket__t));
  if(!hash) return NULL;
  hash->bucket=(ghash_bucket_head__t *)malloc(buck_size *sizeof(ghash_bucket_head__t));
  
  if(!hash->bucket)
  {
     free(hash);
     return NULL;
  }
  for(i=0;i<buck_size; i++)
  {
     dlist_init__r(&hash->bucket[i].head);
     hash->bucket[i].count=0;
  }
  hash->cmp_f=cmp_f;
  hash->key_f=key_f;
  hash->buck_size=buck_size;
  hash->rand_value=rand_value;
#ifdef GHASH_BUCK_STAT
  hash->min=(u32)-1;
  hash->max=0;
#endif  
  return hash;
}

/*Function: 
         Search the hash table, return the node.
  Parameters:
             bash_bucket   hash table
             key           key for comparing
  Return: 
          the node or NULL
 */
dlist_t    *ghash_bucket_search__r(ghash_bucket__t *hash_bucket,GHASH_KEY key)
{
  u32   slot;
  dlist_t *head,*node;

  slot=(*hash_bucket->key_f)(key,hash_bucket->rand_value) % hash_bucket->buck_size;
  head=&hash_bucket->bucket[slot].head;
  node=dlist_next__r(head);
  while(node!=head)
  {
     if((*hash_bucket->cmp_f)(node,key)==1) 
     {
        return node;
     }  
     node=dlist_next__r(node);
  }
  return NULL;
}
/* Function: Insert a new node into hash table
             Please call the function ghash_bucket_search__r to make sure that the node is not stored in hash table
  Parameters:
            hash_bucket  hash table
            node         node to be inserted
            key          to find the hash table index
 */
void  ghash_bucket_insert__r(ghash_bucket__t *hash_bucket,dlist_t *node, GHASH_KEY key)
{
  u32   slot;
  dlist_t *head;

  slot=(*hash_bucket->key_f)(key,hash_bucket->rand_value) % hash_bucket->buck_size;
  head=&hash_bucket->bucket[slot].head;
  dlist_insert_next__r(head,node);
  hash_bucket->bucket[slot].count++;
#ifdef GHASH_BUCK_STAT
  if(hash_bucket->min >hash_bucket->bucket[slot].count) hash_bucket->min =hash_bucket->bucket[slot].count;
  if(hash_bucket->max <hash_bucket->bucket[slot].count) hash_bucket->max =hash_bucket->bucket[slot].count;
#endif
}

/*Function: Delete a node from hahs table. Node should be returned by function ghash_bucket_search__r.
  Parameters:
             hash_bucket  hash table
             node         node to be deleted, from  ghash_bucket_search__r
             key          to find the hash table index           
 */
void   ghash_bucket_delete__r(ghash_bucket__t *hash_bucket,dlist_t *node, GHASH_KEY key)
{
  u32   slot;
  dlist_t *head;

  slot=(*hash_bucket->key_f)(key,hash_bucket->rand_value) % hash_bucket->buck_size;
  head=&hash_bucket->bucket[slot].head;

  hash_bucket->bucket[slot].count--;
  dlist_detach__r(node);
#ifdef GHASH_BUCK_STAT
  if(hash_bucket->min >hash_bucket->bucket[slot].count) hash_bucket->min =hash_bucket->bucket[slot].count;
  if(hash_bucket->max <hash_bucket->bucket[slot].count) hash_bucket->max =hash_bucket->bucket[slot].count;
#endif
}

/*Function:
        Free memory for hash table, the user should make sure that there are no elements in hash table
 */
void  ghash_bucket_destroy__r(ghash_bucket__t *hash_bucket)
{
  free(hash_bucket->bucket);
  free(hash_bucket);
}

/* Function: 
         query the min/max length for collsion elements and their distribution  in hash table.
         
 */
void  ghash_bucket_stat__r(ghash_bucket__t *hash_bucket,ghash_bucket_stat__t *ghash_bucket_stat)
{
  int i;
  memset(ghash_bucket_stat,0,sizeof(ghash_bucket_stat__t));
#ifdef GHASH_BUCK_STAT
  ghash_bucket_stat->min=hash_bucket->min;
  ghash_bucket_stat->max=hash_bucket->max;

  for(i=0;i<hash_bucket->buck_size;i++)
  {
     int count=hash_bucket->bucket[i].count;
     if(count<=4) ghash_bucket_stat->distribution[0]+=count;
     else if(count <=8) ghash_bucket_stat->distribution[1]  +=count;
     else if(count <=16) ghash_bucket_stat->distribution[2] +=count;
     else if(count <=32) ghash_bucket_stat->distribution[3] +=count;
     else ghash_bucket_stat->distribution[4]+=count;
     printf("%d count: %d \n", i, count);
  }
#endif
}

/*
 Function: traverse all the item based on the hash key
           calling the function  trav_f
            
 */
int   g_hash_bucket_traverse__r(ghash_bucket__t *hash_bucket,GHASH_KEY key,GHASH_TRAVERSE_NODE_F trav_f,void * buffer,int max_item)
{
  int sz=0; 
  u32   slot;
  dlist_t *head,*node;

  slot=(*hash_bucket->key_f)(key,hash_bucket->rand_value) % hash_bucket->buck_size;
  head=&hash_bucket->bucket[slot].head;
  node=dlist_next__r(head);
  while(node!=head && sz <max_item)
  {
    buffer=(*trav_f)(node,buffer);
    node=dlist_next__r(node);
    sz++;
  }
  return sz;
}

