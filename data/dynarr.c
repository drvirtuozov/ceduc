#include <ceduc/data/dynarr.h>
#include <ceduc/util/fmt.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

dynarr_t *dynarr_new() {
  dynarr_t *ptr = malloc(sizeof(dynarr_t));

  if (ptr == NULL) {
    fprintf(stderr, "dynarr: failed to create\n");
    return NULL;
  }

  if (pthread_mutex_init(ptr->mtx, NULL)) {
    fprintf(stderr, "dynarr: unable to initalize a mutex\n");
    free(ptr);
    return NULL;
  }

  ptr->len = 0;
  ptr->cap = DYNARR_MIN_CAP;
  ptr->data = calloc(ptr->cap, sizeof(*ptr->data));

  if (ptr->data == NULL) {
    fprintf(stderr, "dynarr: failed to malloc for data\n");
    return NULL;
  }

  return ptr;
}

void dynarr_delete(dynarr_t *ptr) {
  pthread_mutex_destroy(ptr->mtx);
  free(ptr->data);
  ptr->data = NULL;
  free(ptr);
  ptr = NULL;
}

unsigned int __dynarr_push(dynarr_t *ptr, int val) {
  if (ptr->len >= ptr->cap) {
    unsigned int new_cap = ptr->cap;

    while (ptr->len >= new_cap) {
      new_cap <<= 1;
    }

    int *p = realloc(ptr->data, sizeof(*ptr->data) * new_cap);

    if (p == NULL) {
      fprintf(stderr, "dynarr: failed to realloc memory\n");
      return ptr->len;
    }

    ptr->data = p;
    ptr->cap = new_cap;
  }

  ptr->data[ptr->len] = val;
  return ++ptr->len;
}

unsigned int dynarr_push(dynarr_t *ptr, int val) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_push(ptr, val);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}

unsigned int __dynarr_pop(dynarr_t *ptr) {
  if (ptr->len > 0) {
    unsigned int new_cap = ptr->cap >> 1;

    if (ptr->len - 1 <= new_cap && new_cap >= DYNARR_MIN_CAP) {
      int *p = realloc(ptr->data, sizeof(*ptr->data) * new_cap);

      if (p == NULL) {
        fprintf(stderr, "dynarr: failed to realloc memory\n");
        return ptr->len;
      }

      ptr->data = p;
      ptr->cap = new_cap;
    }

    return --ptr->len;
  }

  return ptr->len;
}

unsigned int dynarr_pop(dynarr_t *ptr) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_pop(ptr);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}

unsigned int __dynarr_shift(dynarr_t *ptr) {
  for (unsigned int i = 1; i < ptr->len; i++) {
    ptr->data[i - 1] = ptr->data[i];
  }

  return __dynarr_pop(ptr);
}

unsigned int dynarr_shift(dynarr_t *ptr) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_shift(ptr);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}

unsigned int __dynarr_unshift(dynarr_t *ptr, int val) {
  unsigned int len = __dynarr_push(ptr, val);

  if (len == 1) {
    return len;
  }

  for (unsigned int i = len - 1; i > 0; i--) {
    ptr->data[i] = ptr->data[i - 1];
  }

  ptr->data[0] = val;
  return len;
}

unsigned int dynarr_unshift(dynarr_t *ptr, int val) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_unshift(ptr, val);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}

int __dynarr_get(dynarr_t *ptr, unsigned int i) {
  if (ptr->len >= i) {
    return ptr->data[i];
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
    return __dynarr_push(ptr, val);
  }

  if (ptr->len <= i) {
    ptr->len = i + 1;
  }

  ptr->data[i] = val;
  return ptr->len;
}

unsigned int dynarr_set(dynarr_t *ptr, unsigned int i, int val) {
  pthread_mutex_lock(ptr->mtx);
  unsigned int len = __dynarr_set(ptr, i, val);
  pthread_mutex_unlock(ptr->mtx);
  return len;
}