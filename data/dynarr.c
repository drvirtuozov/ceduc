#include <ceduc/data/dynarr.h>
#include <ceduc/util/fmt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dynarr_t *dynarr_new() {
  dynarr_t *ptr = (dynarr_t *)malloc(sizeof(dynarr_t));

  if (ptr == NULL) {
    fprintf(stderr, "failed to create a dynarr\n");
    return NULL;
  }

  ptr->len = 0;
  ptr->size = sizeof(int[2]);
  return ptr;
}

unsigned int dynarr_push(dynarr_t **ptr, int val) {
  unsigned int cap = (*ptr)->size / sizeof((*ptr)->arr[0]);

  if ((*ptr)->len >= cap) {
    dynarr_t *p =
        (dynarr_t *)realloc(*ptr, sizeof(dynarr_t) + (*ptr)->size * 2);

    if (p == NULL) {
      fprintf(stderr, "failed to realloc memory\n");
      return (*ptr)->len;
    }

    *ptr = p;
    (*ptr)->size = (*ptr)->size * 2;
  }

  (*ptr)->arr[(*ptr)->len] = val;
  return ++(*ptr)->len;
}

char *dynarr_string(dynarr_t *ptr) {
  char *str = (char *)malloc(ptr->len * 32);

  for (int i = 0; i < ptr->len; i++) {
    char s[255];
    sprintf(s, "%d ", ptr->arr[i]);
    strcat(str, s);
  }

  return str;
}

unsigned int dynarr_pop(dynarr_t *ptr) {
  unsigned int cap = ptr->size / sizeof(ptr->arr[0]);

  if (ptr->len > 0) {
    if (ptr->len < cap / 2) {
      dynarr_t *p = (dynarr_t *)realloc(ptr, ptr->size / 2);

      if (p == NULL) {
        fprintf(stderr, "failed to realloc memory\n");
        return ptr->len;
      }

      ptr = p;
      ptr->size = ptr->size / 2;
    }

    return --ptr->len;
  }

  return ptr->len;
}

unsigned int dynarr_shift(dynarr_t *ptr) {
  for (unsigned int i = 1; i < ptr->len; i++) {
    ptr->arr[i - 1] = ptr->arr[i];
  }

  return dynarr_pop(ptr);
}

unsigned int dynarr_unshift(dynarr_t **ptr, int val) {
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

int dynarr_get(dynarr_t *ptr, unsigned int i) { return ptr->arr[i]; }
unsigned int dynarr_set(dynarr_t *ptr, unsigned int i, int val) {
  ptr->arr[i] = val;
  return ptr->len;
}