#ifndef __LLIST_H__
#define __LLIST_H__

#include <stdbool.h>

typedef struct llist_node_t {
  struct llist_node_t *prev;
  int data;
  struct llist_node_t *next;
} llist_node_t;

llist_node_t *llist_node_new(int val);
llist_node_t *llist_gethead(llist_node_t *node);
llist_node_t *llist_gettail(llist_node_t *node);
llist_node_t *llist_get(llist_node_t *node, unsigned int i);
bool llist_set(llist_node_t *node, unsigned int i, int val);
bool llist_add(llist_node_t *node, unsigned int i, llist_node_t *new_node);
unsigned int llist_getlen(llist_node_t *node);
llist_node_t *llist_push(llist_node_t **node, llist_node_t *new_node);
llist_node_t *llist_pop(llist_node_t **node);
llist_node_t *llist_shift(llist_node_t **node);
llist_node_t *llist_unshift(llist_node_t **node, llist_node_t *new_node);
void llist_destroy(llist_node_t **node);

#endif