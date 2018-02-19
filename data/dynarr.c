#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int len;
  size_t size;
  int arr[2];
} dynarr;

int dynarr_push(dynarr **, int);
int dynarr_pop(dynarr *);
int dynarr_shift(dynarr *);
int dynarr_unshift(dynarr *, int);
char *dynarr_string(dynarr *);
dynarr *dynarr_new();

int main() {
  dynarr *arr = dynarr_new();

  if (!arr) {
    printf("failed to create a dynarr\n");
    return 1;
  }

  for (int i = 0; i < 50; i++) {
    dynarr_push(&arr, i);
    printf("\n%s\n", dynarr_string(arr));
  }

  for (int i = 0; i < 50; i++) {
    dynarr_pop(arr);
    printf("\n%s\n", dynarr_string(arr));
  }

  return 0;
}

dynarr *dynarr_new() {
  dynarr *ptr = (dynarr *)malloc(sizeof(dynarr));

  if (ptr == NULL) {
    printf("failed to create a dynamic array\n");
    return NULL;
  }

  ptr->len = 0;
  ptr->size = sizeof(int[2]);
  return ptr;
}

int dynarr_push(dynarr **ptr, int val) {
  unsigned int cap = (*ptr)->size / sizeof((*ptr)->arr[0]);

  if ((*ptr)->len >= cap) {
    dynarr *p = (dynarr *)realloc(*ptr, sizeof(dynarr) + (*ptr)->size * 2);

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

char *dynarr_string(dynarr *ptr) {
  char *str = (char *)malloc(ptr->len * 32);

  for (int i = 0; i < ptr->len; i++) {
    char s[255];
    sprintf(s, "%d ", ptr->arr[i]);
    strcat(str, s);
  }

  return str;
}

int dynarr_pop(dynarr *ptr) {
  unsigned int cap = ptr->size / sizeof(ptr->arr[0]);

  if (ptr->len > 0 && ptr->len < cap / 2) {
    dynarr *p = (dynarr *)realloc(ptr, ptr->size / 2);

    if (p == NULL) {
      printf("failed to realloc memory");
      return ptr->len;
    }

    ptr = p;
    ptr->size = ptr->size / 2;
  }

  return --ptr->len;
}