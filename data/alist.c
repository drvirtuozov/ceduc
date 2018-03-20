#include <ceduc/data/alist.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

alist_node_t *alist_node_new(char *key, char *val) {
  alist_node_t *ptr = malloc(sizeof(alist_node_t));

  if (ptr == NULL) {
    fprintf(stderr, "alist: failed to create");
    return ptr;
  }

  ptr->key = key;
  ptr->value = val;
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
  printf("temp->key: %s, key: %s\n", temp->key, key);
  if (!strcmp(temp->key, key)) {
    temp->value = val;
    return temp;
  }

  while (temp->next != NULL) {
    temp = temp->next;

    if (!strcmp(temp->key, key)) {
      temp->value = val;
      return temp;
    }
  }

  temp->next = new_node;
  printf("temp->next == null: %d\n", temp->next == NULL);
  return temp->next;
}

alist_node_t *alist_get(alist_node_t *node, char *key) {
  if (node == NULL) {
    return node;
  }

  do {
    if (!strcmp(node->key, key)) {
      return node;
    }

    node = node->next;
  } while (node->next != NULL);

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