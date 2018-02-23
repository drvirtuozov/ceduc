#include <ceduc/util/fmt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int len;
  size_t size;
  int arr[2];
} list;

unsigned int list_push(list **, int);
unsigned int list_pop(list *);
unsigned int list_shift(list *);
unsigned int list_unshift(list **, int);
int list_get(list *, unsigned int);
unsigned int list_set(list *, unsigned int i, int val);
char *list_string(list *);
list *list_new();

int main() {
  list *l = list_new();

  if (l == NULL) {
    printf("failed to create a list\n");
    return 1;
  }

  for (int i = 0; i < 50; i++) {
    unsigned int len = list_push(&l, i);
    // printf("\n(len:%d) %s\n", len, list_string(arr));
    printarr(l->arr, l->len);
  }

  for (int i = 0; i < 50; i++) {
    unsigned int len = list_shift(l);
    // printf("\n(len:%d) %s\n", len, list_string(arr));
    printarr(l->arr, l->len);
  }

  for (int i = 0; i < 50; i++) {
    unsigned int len = list_unshift(&l, i);
    // printf("\n(len:%d) %s\n", len, list_string(arr));
    printarr(l->arr, l->len);
  }

  return 0;
}

list *list_new() {
  list *ptr = (list *)malloc(sizeof(list));

  if (ptr == NULL) {
    printf("failed to create a list\n");
    return NULL;
  }

  ptr->len = 0;
  ptr->size = sizeof(int[2]);
  return ptr;
}

unsigned int list_push(list **ptr, int val) {
  unsigned int cap = (*ptr)->size / sizeof((*ptr)->arr[0]);

  if ((*ptr)->len >= cap) {
    list *p = (list *)realloc(*ptr, sizeof(list) + (*ptr)->size * 2);

    if (p == NULL) {
      printf("failed to realloc memory");
      return (*ptr)->len;
    }

    *ptr = p;
    (*ptr)->size = (*ptr)->size * 2;
  }

  (*ptr)->arr[(*ptr)->len] = val;
  return ++(*ptr)->len;
}

char *list_string(list *ptr) {
  char *str = (char *)malloc(ptr->len * 32);

  for (int i = 0; i < ptr->len; i++) {
    char s[255];
    sprintf(s, "%d ", ptr->arr[i]);
    strcat(str, s);
  }

  return str;
}

unsigned int list_pop(list *ptr) {
  unsigned int cap = ptr->size / sizeof(ptr->arr[0]);

  if (ptr->len > 0) {
    if (ptr->len < cap / 2) {
      list *p = (list *)realloc(ptr, ptr->size / 2);

      if (p == NULL) {
        printf("failed to realloc memory");
        return ptr->len;
      }

      ptr = p;
      ptr->size = ptr->size / 2;
    }

    return --ptr->len;
  }

  return ptr->len;
}

unsigned int list_shift(list *ptr) {
  for (unsigned int i = 1; i < ptr->len; i++) {
    ptr->arr[i - 1] = ptr->arr[i];
  }

  return list_pop(ptr);
}

unsigned int list_unshift(list **ptr, int val) {
  unsigned int len = list_push(ptr, val);

  if (len == 1) {
    return len;
  }

  for (unsigned int i = len - 1; i > 0; i--) {
    (*ptr)->arr[i] = (*ptr)->arr[i - 1];
  }

  (*ptr)->arr[0] = val;
  return len;
}

int list_get(list *ptr, unsigned int i) { return ptr->arr[i]; }
unsigned int list_set(list *ptr, unsigned int i, int val) {
  ptr->arr[i] = val;
  return ptr->len;
}