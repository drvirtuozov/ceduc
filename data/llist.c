#include <ceduc/data/llist.h>
#include <stdio.h>
#include <stdlib.h>

llist_node_t *llist_node_new(int val) {
  llist_node_t *ptr = (llist_node_t *)malloc(sizeof(llist_node_t));
  ptr->data = val;
  return ptr;
}

llist_node_t *llist_node_gethead(llist_node_t *node) {
  if (node == NULL) {
    return node;
  }

  while (node->prev != NULL) {
    node = node->prev;
  }

  return node;
}

llist_node_t *llist_node_gettail(llist_node_t *node) {
  if (node == NULL) {
    return node;
  }

  while (node->next != NULL) {
    node = node->next;
  }

  return node;
}

unsigned int llist_node_getlen(llist_node_t *head) {
  unsigned int len = 0;
  head = llist_node_gethead(head);

  if (head == NULL) {
    return len;
  } else {
    len++;
  }

  while (head->next != NULL) {
    head = head->next;
    len++;
  }

  return len;
}

llist_node_t *llist_node_push(llist_node_t *head, llist_node_t *new_node) {
  llist_node_t *tail = llist_node_gettail(head);
  tail->next = new_node;
  new_node->prev = tail;
  return llist_node_gethead(head);
}

llist_node_t *llist_node_pop(llist_node_t *head) {
  llist_node_t *tail = llist_node_gettail(head);
  tail->prev->next = NULL;
  return tail;
}

llist_node_t *llist_node_shift(llist_node_t *head) {
  head = llist_node_gethead(head);
  llist_node_t *prev = head->prev;
  *head = *head->next;
  head->prev = NULL;
  return prev;
}

llist_node_t *llist_node_unshift(llist_node_t *head, llist_node_t *new_node) {
  head = llist_node_gethead(head);
  new_node->next = head;
  head->prev = new_node;
  return head;
}