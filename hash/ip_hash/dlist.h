#ifndef _APP_DLIST_H__
#define _APP_DLIST_H__
/*
 Implementing the basic functionality for double cyclical list.
 Interface:
      void    dlist_init__r(dlist_t *head)
      void    dlist_insert_next__r(dlist_t *node,dlist_t *to_insert)
      void    dlist_insert_prev__r(dlist_t *node,dlist_t *to_insert)
      dlist_t * dlist_prev__r(dlist_t *node)
      dlist_t * dlist_next__r(dlist_t *node)
      int     dlist_empty__r(dlist_t *head)
      void    dlist_detach__r(dlist_t *node)
      DLIST_ENTRY(ptr,type,name)
*/
typedef struct dlist_t
{
   struct dlist_t *next;
   struct dlist_t *prev;
}dlist_t;

static inline  void      dlist_init__r(dlist_t *head)
{
  head->next=head->prev=head;
}


/*
  Insert a node between node and node->next.
*/
static inline void      dlist_insert_next__r(dlist_t *node,dlist_t *to_insert)
{
  dlist_t *tmp=node->next;
  node->next=to_insert;   to_insert->next=tmp;
  tmp->prev=to_insert;    to_insert->prev=node;
}

/*
   Insert a node between node->prev and node.
*/
static inline void      dlist_insert_prev__r(dlist_t *node,dlist_t *to_insert)
{
  dlist_t *tmp=node->prev;
  tmp->next=to_insert; to_insert->next=node;
  node->prev=to_insert; to_insert->prev=tmp;
}

static inline dlist_t  *dlist_next__r(dlist_t *node)
{
  return node->next;
}
static inline dlist_t  *dlist_prev__r(dlist_t *node)
{
  return node->prev;
}
static inline int       dlist_empty__r(dlist_t *head)
{
  return  (head->next==head && head->prev==head)? 1:0;
}

static inline void      dlist_detach__r(dlist_t *node)
{
  struct dlist_t *nxt=node->next,*prv=node->prev;
  prv->next=nxt;
  nxt->prev=prv;
  node->next=node->prev=node;
}

/*
   ptr  : pointer to struct dlist_t
   type : the name of a strut that containing  an element with type dlist_t
   name : the name of the element in type
*/
#define DLIST_ENTRY(ptr,type,name)  \
   ((type *)((unsigned long)ptr -((unsigned long)(&((type *)0)->name))))

#endif
