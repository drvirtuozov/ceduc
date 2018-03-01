#include <ceduc/data/dynarr.h>
#include <ceduc/util/fmt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dynarr_t *dynarr_new() {
  dynarr_t *ptr = (dynarr_t *)malloc(sizeof(dynarr_t));

  if (ptr == NULL) {
    fprintf(stderr, "failed to create a dynarr\n");
    return NULL;
  }

  int mtx_res = pthread_mutex_init(ptr->mtx, NULL);

  if (mtx_res != 0) {
    fprintf(stderr, "unable to initalize a dynarr mutex\n");
    return NULL;
  }

  ptr->len = 0;
  ptr->cap = 2;
  return ptr;
}

unsigned int __dynarr_push(dynarr_t **ptr, int val) {
  if ((*ptr)->len >= (*ptr)->cap) {
    unsigned int new_cap = (*ptr)->cap;

    while ((*ptr)->len >= new_cap) {
      new_cap *= 2;
    }

    size_t new_size = new_cap * sizeof((*ptr)->arr[0]);
    dynarr_t *p = (dynarr_t *)realloc(*ptr, sizeof(dynarr_t) + new_size);

    if (p == NULL) {
      fprintf(stderr, "failed to realloc memory\n");
      return (*ptr)->len;
    }

    *ptr = p;
    (*ptr)->cap = new_cap;
  }

  (*ptr)->arr[(*ptr)->len] = val;
  return ++(*ptr)->len;
}

unsigned int dynarr_push(dynarr_t **ptr, int val) {
  pthread_mutex_lock((*ptr)->mtx);
  unsigned int len = __dynarr_push(ptr, val);
  pthread_mutex_unlock((*ptr)->mtx);
  return len;
}

char *__dynarr_string(dynarr_t *ptr) {
  char *str = (char *)malloc(ptr->len * 32);

  for (int i = 0; i < ptr->len; i++) {
    char s[255];
    sprintf(s, "%d ", ptr->arr[i]);
    strcat(str, s);
  }

  return str;
}

char *dynarr_string(dynarr_t *ptr) {
  pthread_mutex_lock(ptr->mtx);
  char *str = __dynarr_string(ptr);
  pthread_mutex_unlock(ptr->mtx);
  return str;
}

unsigned int __dynarr_pop(dynarr_t **ptr) {
  unsigned int len = 0;

  if ((*ptr)->len > 0) {
    if ((*ptr)->len < (*ptr)->cap / 2) {
      unsigned int new_cap = (*ptr)->cap / 2;
      size_t new_size = new_cap * sizeof((*ptr)->arr[0]);
      dynarr_t *p = (dynarr_t *)realloc(*ptr, sizeof(dynarr_t) + new_size);

      if (p == NULL) {
        fprintf(stderr, "failed to realloc memory\n");
        return (*ptr)->len;
      }

      (*ptr) = p;
      (*ptr)->cap = new_cap;
    }

    len = --(*ptr)->len;
  }

  return len;
}

unsigned int dynarr_pop(dynarr_t *ptr) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_pop(&ptr);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}

unsigned int __dynarr_shift(dynarr_t *ptr) {
  for (unsigned int i = 1; i < ptr->len; i++) {
    ptr->arr[i - 1] = ptr->arr[i];
  }

  return __dynarr_pop(&ptr);
}

unsigned int dynarr_shift(dynarr_t *ptr) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_shift(ptr);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}

unsigned int __dynarr_unshift(dynarr_t **ptr, int val) {
  unsigned int len = __dynarr_push(ptr, val);

  if (len == 1) {
    return len;
  }

  for (unsigned int i = len - 1; i > 0; i--) {
    (*ptr)->arr[i] = (*ptr)->arr[i - 1];
  }

  (*ptr)->arr[0] = val;
  return len;
}

unsigned int dynarr_unshift(dynarr_t **ptr, int val) {
  pthread_mutex_lock((*ptr)->mtx);
  unsigned int len = __dynarr_unshift(ptr, val);
  pthread_mutex_unlock((*ptr)->mtx);
  return len;
}

int __dynarr_get(dynarr_t *ptr, unsigned int i) {
  if (ptr->len >= i) {
    return ptr->arr[i];
  }

  return 0;
}

int dynarr_get(dynarr_t *ptr, unsigned int i) {
  pthread_mutex_lock(ptr->mtx);
  int val = __dynarr_get(ptr, i);
  pthread_mutex_unlock(ptr->mtx);
  return val;
}

unsigned int __dynarr_set(dynarr_t *ptr, unsigned int i, int val) {
  if (ptr->cap <= i) {
    ptr->len = i;
    return __dynarr_push(&ptr, val);
  }

  if (ptr->len <= i) {
    ptr->len = i + 1;
  }

  ptr->arr[i] = val;
  return ptr->len;
}

unsigned int dynarr_set(dynarr_t *ptr, unsigned int i, int val) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_set(ptr, i, val);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}