#ifndef LLIST_H
#define LLIST_H

typedef struct llist_node_t {
  struct llist_node_t *prev;
  int data;
  struct llist_node_t *next;
} llist_node_t;

llist_node_t *llist_node_new(int val);
unsigned int llist_node_push(llist_node_t *head, llist_node_t *new_node);

#endif