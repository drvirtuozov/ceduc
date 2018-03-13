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
    llist_node_push(llist, new_node);
    printf("llist_node_push len: %d\n", llist_node_getlen(llist));
    printlist(llist);
  }

  for (int i = 1; i < ARR_LEN; i++) {
    llist_node_t *last = llist_node_pop(llist);
    printf("llist_node_pop len: %d\n", llist_node_getlen(llist));
    printlist(llist);
    free(last);
  }

  for (int i = 1; i < ARR_LEN; i++) {
    llist_node_t *new_node = llist_node_new(i);
    llist_node_push(llist, new_node);
    printf("llist_node_push len: %d\n", llist_node_getlen(llist));
    printlist(llist);
  }

  for (int i = 1; i < ARR_LEN; i++) {
    llist_node_t *first = llist_node_shift(llist);
    printf("llist_node_shift len: %d\n", llist_node_getlen(llist));
    printlist(llist);
    free(first);
  }

  for (int i = 1; i < ARR_LEN; i++) {
    llist_node_t *new_node = llist_node_new(i);
    llist_node_unshift(llist, new_node);
    printf("llist_node_unshift len: %d\n", llist_node_getlen(llist));
    printlist(llist);
  }

  printf("llist_node_get index: %d, value: %d\n", 6,
         llist_node_get(llist, 6)->data);

  printf("llist_node_set index: %d, value: 13, result: %d\n", 6,
         llist_node_set(llist, 6, 13));

  printlist(llist);

  return 0;
}
