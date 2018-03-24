#include <ceduc/data/alist.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

alist_node_t *alist_node_new(wchar_t *key, wchar_t *val) {
  alist_node_t *ptr = malloc(sizeof(alist_node_t));
  wchar_t *k = malloc(wcslen(key) + 1);
  wchar_t *v = malloc(wcslen(val) + 1);

  if (ptr == NULL) {
    fprintf(stderr, "alist: failed to create");
    return ptr;
  }

  ptr->key = wcscpy(k, key);
  ptr->value = wcscpy(v, val);
  ptr->next = NULL;
  return ptr;
}

alist_node_t *alist_add(alist_node_t **node, wchar_t *key, wchar_t *val) {
  alist_node_t *new_node = alist_node_new(key, val);

  if (*node == NULL) {
    *node = new_node;
    return new_node;
  }

  alist_node_t *temp = *node;

  do {
    if (!wcscmp(temp->key, new_node->key)) {
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

alist_node_t *alist_get(alist_node_t *node, wchar_t *key) {
  if (node == NULL) {
    return node;
  }

  while (node != NULL) {
    if (!wcscmp(node->key, key)) {
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

alist_node_t *alist_delete(alist_node_t **head, wchar_t *key) {
  if (*head == NULL) {
    return *head;
  }

  alist_node_t *node = *head;

  if (!wcscmp(node->key, key)) {
    *head = node->next;
    return node;
  }

  alist_node_t *prev = NULL;

  while (node->next != NULL) {
    if (!wcscmp(node->key, key)) {
      prev->next = node->next;
      return node;
    }

    prev = node;
    node = node->next;
  }

  return NULL;
}