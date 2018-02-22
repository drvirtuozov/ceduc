#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  unsigned int len;
  size_t size;
  int arr[2];
} dynarr;

unsigned int dynarr_push(dynarr **, int);
unsigned int dynarr_pop(dynarr *);
unsigned int dynarr_shift(dynarr *);
unsigned int dynarr_unshift(dynarr **, int);
int dynarr_get(dynarr *, unsigned int);
unsigned int dynarr_set(dynarr *, unsigned int i, int val);
char *dynarr_string(dynarr *);
dynarr *dynarr_new();

int main() {
  dynarr *arr = dynarr_new();

  if (arr == NULL) {
    printf("failed to create a dynarr\n");
    return 1;
  }

  for (int i = 0; i < 50; i++) {
    unsigned int len = dynarr_push(&arr, i);
    printf("\n(len:%d) %s\n", len, dynarr_string(arr));
  }

  for (int i = 0; i < 50; i++) {
    unsigned int len = dynarr_shift(arr);
    printf("\n(len:%d) %s\n", len, dynarr_string(arr));
  }

  for (int i = 0; i < 50; i++) {
    unsigned int len = dynarr_unshift(&arr, i);
    printf("\n(len:%d) %s\n", len, dynarr_string(arr));
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

unsigned int dynarr_push(dynarr **ptr, int val) {
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

unsigned int dynarr_pop(dynarr *ptr) {
  unsigned int cap = ptr->size / sizeof(ptr->arr[0]);

  if (ptr->len > 0) {
    if (ptr->len < cap / 2) {
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

  return ptr->len;
}

unsigned int dynarr_shift(dynarr *ptr) {
  for (unsigned int i = 1; i < ptr->len; i++) {
    ptr->arr[i - 1] = ptr->arr[i];
  }

  return dynarr_pop(ptr);
}

unsigned int dynarr_unshift(dynarr **ptr, int val) {
  unsigned int len = dynarr_push(ptr, val);

  if (len == 1) {
    return len;
  }

  for (unsigned int i = len - 1; i > 0; i--) {
    (*ptr)->arr[i] = (*ptr)->arr[i - 1];
  }

  (*ptr)->arr[0] = val;
  return len;
}

int dynarr_get(dynarr *ptr, unsigned int i) { return ptr->arr[i]; }
unsigned int dynarr_set(dynarr *ptr, unsigned int i, int val) {
  ptr->arr[i] = val;
}