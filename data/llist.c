#include <ceduc/data/llist.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

llist_node_t *llist_node_new(int val) {
  llist_node_t *ptr = malloc(sizeof(llist_node_t));
  ptr->data = val;
  ptr->prev = NULL;
  ptr->next = NULL;
  return ptr;
}

llist_node_t *llist_gethead(llist_node_t *node) {
  if (node == NULL) {
    return node;
  }

  while (node->prev != NULL) {
    node = node->prev;
  }

  return node;
}

llist_node_t *llist_gettail(llist_node_t *node) {
  if (node == NULL) {
    return node;
  }

  while (node->next != NULL) {
    node = node->next;
  }

  return node;
}

unsigned int llist_getlen(llist_node_t *head) {
  unsigned int len = 0;
  head = llist_gethead(head);

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

llist_node_t *llist_push(llist_node_t **head, llist_node_t *new_node) {
  if (*head == NULL) {
    *head = new_node;
    return new_node;
  }

  llist_node_t *tail = llist_gettail(*head);
  tail->next = new_node;
  new_node->prev = tail;
  return llist_gethead(*head);
}

llist_node_t *llist_pop(llist_node_t **head) {
  if (*head == NULL) {
    return *head;
  }

  llist_node_t *tail = llist_gettail(*head);

  if (tail->prev != NULL) {
    tail->prev->next = NULL;
  } else {
    *head = NULL;
  }

  return tail;
}

llist_node_t *llist_shift(llist_node_t **node) {
  if (*node == NULL) {
    return *node;
  }

  llist_node_t *head = llist_gethead(*node);

  if (head->next != NULL) {
    head->next->prev = NULL;
    *node = head->next;
  } else {
    *node = NULL;
  }

  return head;
}

llist_node_t *llist_unshift(llist_node_t **node, llist_node_t *new_node) {
  if (*node == NULL) {
    *node = new_node;
    return new_node;
  }

  llist_node_t *head = llist_gethead(*node);
  head->prev = new_node;
  new_node->next = head;
  *node = new_node;
  return new_node;
}

llist_node_t *llist_get(llist_node_t *node, unsigned int index) {
  if (node == NULL) {
    return node;
  }

  node = llist_gethead(node);

  for (unsigned int i = 0; i < index; i++) {
    if (node->next != NULL) {
      node = node->next;
    } else {
      return NULL;
    }
  }

  return node;
}

bool llist_set(llist_node_t *node, unsigned int index, int val) {
  if (node == NULL) {
    return node;
  }

  node = llist_gethead(node);

  for (unsigned int i = 0; i < index; i++) {
    if (node->next != NULL) {
      node = node->next;
    } else {
      return false;
    }
  }

  node->data = val;
  return true;
}

bool llist_add(llist_node_t *node, unsigned int index, llist_node_t *new_node) {
  if (node == NULL) {
    return node;
  }

  node = llist_gethead(node);

  for (unsigned int i = 0; i < index; i++) {
    if (node->next != NULL) {
      node = node->next;
    } else {
      return false;
    }
  }

  llist_node_t *prev_temp = node->prev;
  llist_node_t *next_temp = node;
  prev_temp->next = new_node;
  new_node->prev = prev_temp;
  new_node->next = next_temp;
  next_temp->prev = new_node;
  return true;
}

void llist_destroy(llist_node_t **node) {
  llist_node_t *head = llist_gethead(*node);

  if (head != NULL) {
    while (head->next != NULL) {
      head = head->next;
      free(head->prev);
      head->prev = NULL;
    }

    free(head);
    *node = NULL;
  }
}