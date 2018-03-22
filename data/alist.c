#include <ceduc/data/alist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

alist_node_t *alist_node_new(char *key, char *val) {
  alist_node_t *ptr = malloc(sizeof(alist_node_t));
  char *k = malloc(sizeof(char *));
  char *v = malloc(sizeof(char *));
  strcpy(k, key);
  strcpy(v, val);

  if (ptr == NULL) {
    fprintf(stderr, "alist: failed to create");
    return ptr;
  }

  ptr->key = k;
  ptr->value = v;
  ptr->next = NULL;
  return ptr;
}

alist_node_t *alist_add(alist_node_t **node, char *key, char *val) {
  alist_node_t *new_node = alist_node_new(key, val);

  if (*node == NULL) {
    *node = new_node;
    return new_node;
  }

  alist_node_t *temp = *node;

  do {
    if (!strcmp(temp->key, new_node->key)) {
      temp->value = new_node->value;
      return temp;
    }

    if (temp->next == NULL) {
      break;
    }

    temp = temp->next;
  } while (temp->next != NULL);

  temp->next = new_node;
  return new_node;
}

alist_node_t *alist_get(alist_node_t *node, char *key) {
  if (node == NULL) {
    return node;
  }

  while (node != NULL) {
    if (!strcmp(node->key, key)) {
      return node;
    }

    node = node->next;
  }

  return NULL;
}

unsigned int alist_getlen(alist_node_t *node) {
  unsigned int len = 0;

  if (node == NULL) {
    return len;
  } else {
    len++;
  }

  while (node->next != NULL) {
    node = node->next;
    len++;
  }

  return len;
}