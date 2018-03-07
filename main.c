#include <ceduc/data/dynarr.h>
#include <ceduc/data/llist.h>
#include <ceduc/sort/bubble.h>
#include <ceduc/util/fmt.h>
#include <ceduc/util/sort.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 13

int run_dynarr_tasks();
int run_llist_tasks();

int main(int argc, char *argv[]) {
  int err = 0;
  /* err = run_dynarr_tasks();

  if (err != 0) {
    return err;
  } */

  err = run_llist_tasks();

  if (err != 0) {
    return err;
  }

  return err;
}

int run_dynarr_tasks() {
  dynarr_t *dynarr = dynarr_new();

  if (dynarr == NULL) {
    printf("failed to create a dynarr\n");
    return 1;
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("pushing to dynarr...\n");
    unsigned int len = dynarr_push(&dynarr, i);
    // printf("\n(len:%d) %s\n", len, dynarr_string(arr));
    printarr(dynarr->arr, dynarr->len);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("shifting from dynarr...\n");
    unsigned int len = dynarr_shift(dynarr);
    // printf("\n(len:%d) %s\n", len, dynarr_string(arr));
    printarr(dynarr->arr, dynarr->len);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("unshifting to dynarr...\n");
    unsigned int len = dynarr_unshift(&dynarr, i);
    // printf("\n(len:%d) %s\n", len, dynarr_string(arr));
    printarr(dynarr->arr, dynarr->len);
  }

  printf("bubble sorting dynarr...\n");
  sort_bubble(dynarr->arr, dynarr->len);
  printarr(dynarr->arr, dynarr->len);

  printf("dynarr_get index: %d, value: %d\n", 12, dynarr_get(dynarr, 12));

  printf("dynarr_set index: 6, value: 666, len: %d, cap: %d\n",
         dynarr_set(dynarr, 6, 666), dynarr->cap);
  printarr(dynarr->arr, dynarr->len);
  free(dynarr);
  return 0;
}

int run_llist_tasks() {
  llist_node_t *llist = llist_node_new(0);

  if (llist == NULL) {
    printf("failed to create a llist\n");
    return 1;
  }

  for (int i = 1; i < ARR_LEN; i++) {
    llist_node_t *new_node = llist_node_new(i);
    printf("llist_node_push len: %d\n", llist_node_push(llist, new_node));
  }

  free(llist); // memory leak
  return 0;
}
