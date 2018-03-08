#include <ceduc/data/llist.h>
#include <stdio.h>
#include <stdlib.h>

llist_node_t *llist_node_new(int val) {
  llist_node_t *ptr = (llist_node_t *)malloc(sizeof(llist_node_t));
  ptr->data = val;
  return ptr;
}

unsigned int llist_node_push(llist_node_t *head, llist_node_t *new_node) {
  unsigned int len = 2;

  if (head->next == NULL) {
    new_node->prev = head;
    head->next = new_node;
    return len;
  }

  llist_node_t *temp = head->next;

  while (temp->next != NULL) {
    temp = temp->next;
    len++;
  }

  new_node->prev = temp;
  temp->next = new_node;
  return ++len;
}

unsigned int llist_node_pop(llist_node_t *head) {
  unsigned int len = 0;

  if (head->next == NULL) {
    head = NULL;
    free(head);
    return len;
  }

  llist_node_t *temp = head;

  while (temp->next != NULL) {
    temp = temp->next;
    len++;
  }

  temp->prev->next = NULL;
  free(temp);
  return len;
}