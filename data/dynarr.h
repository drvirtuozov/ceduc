#include <pthread.h>
#include <stdlib.h>

typedef struct {
  pthread_mutex_t *mtx;
  unsigned int len;
  unsigned int cap;
  int *data;
} dynarr_t;

unsigned int dynarr_push(dynarr_t *, int);
unsigned int dynarr_pop(dynarr_t *);
unsigned int dynarr_shift(dynarr_t *);
unsigned int dynarr_unshift(dynarr_t *, int);
int dynarr_get(dynarr_t *, unsigned int);
unsigned int dynarr_set(dynarr_t *, unsigned int i, int val);
dynarr_t *dynarr_new();
void dynarr_delete(dynarr_t *ptr);