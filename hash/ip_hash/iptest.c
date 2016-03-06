#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlist.h"
#include "ghash_bucket.h"
#include "jhash.h"
#define IP_ADDR_T_IPV4_C 0x0
#define IP_ADDR_T_IPV6_C 0x1
#define IP_HASH_BUCKET_SZ   2039
#define MAX_IP_ADDR_NBR     2200
#define IP_ADDR_T_SIZE_C 16
typedef struct
{
   char  version;
   union
   {
      char    addr[IP_ADDR_T_SIZE_C]; 
      int     value[IP_ADDR_T_SIZE_C/sizeof(int)];
   };
}ip_addr__t;

#define GET_IP_ADDR__T(ip_in,ip_out) do{\
          (ip_out)->version=(ip_in)->version;                   \
          memcpy((ip_out)->addr,(ip_in)->addr,IP_ADDR_T_SIZE_C);    \
       }while(0)

typedef struct
{
    dlist_t                        list;
    ip_addr__t                     ip_addr;
    int                            reference;
}app_ip_addr__t;

typedef struct
{
    app_ip_addr__t                ip_addr_storage[MAX_IP_ADDR_NBR];
    ghash_bucket__t              *ip_addr_hash;
    dlist_t                       free_head;
    int                           rand_value;
}ip_addr_factory__t;

static int  ip_hash_equal__r(dlist_t *node,GHASH_KEY key)
{
  ip_addr__t *ip1,*ip2;
  app_ip_addr__t *iphash=DLIST_ENTRY(node,app_ip_addr__t,list);
  int    result=0;

  ip1=&iphash->ip_addr;
  ip2=(ip_addr__t *)key;

  if( ip1->version == ip2->version)
  {
     if(ip1->version == IP_ADDR_T_IPV4_C)
     {
        result=(ip1->value[0]==ip2->value[0]) ? 1:0;
     }
     else
     {
        result=((ip1->value[3]==ip2->value[3]  && ip1->value[2]==ip2->value[2]  &&
                 ip1->value[1]==ip2->value[1]  && ip1->value[0]==ip2->value[0])? 1:0);
     }
  }
  else
  {
     result=0;
  }
  return  result;
}

static u32  ip_hash_slot__r(GHASH_KEY key,u32 rand_value)
{
  ip_addr__t *ip=(ip_addr__t *)key;
  if(ip->version==IP_ADDR_T_IPV4_C)
     return (u32)ip->value[0];
  else return (u32)jhash(ip->addr,sizeof(ip->addr),rand_value);
}

ip_addr_factory__t ip_addr_factory;
#define GET_APP_IP_HANDLE(app_ip_addr)  \
            ((int)(app_ip_addr - ip_addr_factory.ip_addr_storage))

int  init_hash()
{
  int rand_value, i;
  rand_value = (int) rand();
  ip_addr_factory.ip_addr_hash=ghash_bucket_create__r(IP_HASH_BUCKET_SZ,ip_hash_equal__r,ip_hash_slot__r,rand_value);
  if(ip_addr_factory.ip_addr_hash == NULL)
  {
     printf("hash init failed \n");
     exit(-1);
  }
  dlist_init__r(&ip_addr_factory.free_head);
  for(i=0;i<MAX_IP_ADDR_NBR;i++)
  {
     memset(&ip_addr_factory.ip_addr_storage[i], 0, sizeof(app_ip_addr__t));
     dlist_init__r(&ip_addr_factory.ip_addr_storage[i].list);
     dlist_insert_next__r(&ip_addr_factory.free_head,&ip_addr_factory.ip_addr_storage[i].list);
  }
  return 0;
}

void destroy_hash()
{
    ghash_bucket_destroy__r(ip_addr_factory.ip_addr_hash);
}

int add_ip_addr_r( ip_addr__t*  p_ip_addr_in_ptr,
                   int*        p_ip_idx )
{
  ip_addr__t   ip_addr;
  dlist_t     *node;
  app_ip_addr__t *app_ip_addr = NULL;
  int status = -2;

  GET_IP_ADDR__T(p_ip_addr_in_ptr,&ip_addr);
  /* We must assure memory layout as we think. */
    if((p_ip_addr_in_ptr -> version != IP_ADDR_T_IPV4_C) &&
       (p_ip_addr_in_ptr -> version != IP_ADDR_T_IPV6_C) )
    {
        printf("IP address version %d is invalid",
                p_ip_addr_in_ptr -> version );            
        return -2;
    }
    node=ghash_bucket_search__r(ip_addr_factory.ip_addr_hash,(GHASH_KEY)&ip_addr);
    if(node!=NULL) 
    {
        app_ip_addr=DLIST_ENTRY(node,app_ip_addr__t,list);
        app_ip_addr->reference++;
    }
    else 
    {
       if(dlist_empty__r(&ip_addr_factory.free_head))
       {
          status=-1;
       }
       else 
       {
          node=dlist_prev__r(&ip_addr_factory.free_head);
          dlist_detach__r(node);
          app_ip_addr=DLIST_ENTRY(node,app_ip_addr__t,list);

          /*Initialization of app_ip_addr__t*/
          dlist_init__r(&app_ip_addr->list);
          memcpy(&app_ip_addr->ip_addr,&ip_addr,sizeof(ip_addr));
          app_ip_addr->reference=1; 

          ghash_bucket_insert__r(ip_addr_factory.ip_addr_hash,node,(GHASH_KEY)(&ip_addr));
       }
    }
    *p_ip_idx = GET_APP_IP_HANDLE(app_ip_addr);
   return 0;
}
print_ip(ip_addr__t *ip)
{
    printf("IP: %3d.%3d.%3d.%3d\n",ip->addr[0],ip->addr[1],ip->addr[2],ip->addr[3]);
}
int main()
{
    
    int i;
    ip_addr__t ip;
    int idx;
    ghash_bucket_stat__t *ghash_bucket_stat;
    srand(time(NULL));
    ip.version =  IP_ADDR_T_IPV4_C;
    ip.addr[0]=1;   ip.addr[1]=2;   ip.addr[2]=3; ip.addr[3]=4;
    
    init_hash();
    printf("init done\n");
    for(i=0;i<MAX_IP_ADDR_NBR;i++)
    {
        ip.value[0]=(int)rand();
        add_ip_addr_r(&ip, &idx);
    }

    ghash_bucket_stat__r(ip_addr_factory.ip_addr_hash, ghash_bucket_stat);
     /*0:   <= 4
       1:   <=8
       2:   <=16
       3:   <=32
       4:   >32
             */

    printf("Hash min: %d, max: %d\n distribution: [0-4]:%d\n, [5-8]:%d, [9-16]:%d, [17-32]:%d, [33-]:%d\n", ghash_bucket_stat->min, \
                                                           ghash_bucket_stat->max, \
                                                           ghash_bucket_stat->distribution[0], \
                                                           ghash_bucket_stat->distribution[1], \
                                                           ghash_bucket_stat->distribution[2], \
                                                           ghash_bucket_stat->distribution[3], \
                                                           ghash_bucket_stat->distribution[4]);
//    for(i=0;i<IP_HASH_BUCKET_SZ;i++)
//        printf("%d count: %d \n", i, ((ip_addr_factory.ip_addr_hash)->bucket[i]).count);

    destroy_hash();

    return 0;
}
