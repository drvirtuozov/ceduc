#ifndef __LLIST_H__
#define __LLIST_H__

#include <stdbool.h>

typedef struct llist_node_t {
  struct llist_node_t *prev;
  int data;
  struct llist_node_t *next;
} llist_node_t;

llist_node_t *llist_node_new(int val);
llist_node_t *llist_node_gethead(llist_node_t *node);
llist_node_t *llist_node_gettail(llist_node_t *node);
llist_node_t *llist_node_get(llist_node_t *node, unsigned int i);
bool llist_node_set(llist_node_t *node, unsigned int i, int val);
unsigned int llist_node_getlen(llist_node_t *node);
llist_node_t *llist_node_push(llist_node_t *node, llist_node_t *new_node);
llist_node_t *llist_node_pop(llist_node_t *node);
llist_node_t *llist_node_shift(llist_node_t *node);
llist_node_t *llist_node_unshift(llist_node_t *node, llist_node_t *new_node);

#endif