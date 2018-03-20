#include <ceduc/data/alist.h>
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
int run_alist_tasks();

int main(int argc, char *argv[]) {
  int err = 0;

  err = run_dynarr_tasks();

  if (err != 0) {
    return err;
  }

  err = run_llist_tasks();

  if (err != 0) {
    return err;
  }

  err = run_alist_tasks();

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
    printf("dynarr_push len: %d, cap: %d\n", dynarr_push(dynarr, i),
           dynarr->cap);
    printarr(dynarr->data, dynarr->len);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("dynarr_pop len: %d, cap: %d\n", dynarr_pop(dynarr), dynarr->cap);
    printarr(dynarr->data, dynarr->len);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("dynarr_unshift len: %d, cap: %d\n", dynarr_unshift(dynarr, i),
           dynarr->cap);
    printarr(dynarr->data, dynarr->len);
  }

  printf("sort_bubble dynarr...\n");
  sort_bubble(dynarr->data, dynarr->len);
  printarr(dynarr->data, dynarr->len);

  printf("dynarr_get index: %d, value: %d\n", 12, dynarr_get(dynarr, 12));

  printf("dynarr_set index: 6, value: 666, len: %d, cap: %d\n",
         dynarr_set(dynarr, 6, 666), dynarr->cap);
  printarr(dynarr->data, dynarr->len);

  for (int i = 0; i < ARR_LEN; i++) {
    printf("dynarr_shift len: %d, cap: %d\n", dynarr_shift(dynarr),
           dynarr->cap);
    printarr(dynarr->data, dynarr->len);
  }

  dynarr_delete(dynarr);
  return 0;
}

int run_llist_tasks() {
  llist_node_t *llist = NULL;

  for (int i = 0; i < ARR_LEN; i++) {
    llist_push(&llist, llist_node_new(i));
    printf("llist_push len: %d\n", llist_getlen(llist));
    printlist(llist);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    free(llist_pop(&llist));
    printf("llist_pop len: %d\n", llist_getlen(llist));
    printlist(llist);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    llist_push(&llist, llist_node_new(i));
    printf("llist_push len: %d\n", llist_getlen(llist));
    printlist(llist);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    free(llist_shift(&llist));
    printf("llist_shift len: %d\n", llist_getlen(llist));
    printlist(llist);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    llist_unshift(&llist, llist_node_new(i));
    printf("llist_unshift len: %d\n", llist_getlen(llist));
    printlist(llist);
  }

  printf("llist_get index: %d, value: %d\n", 6, llist_get(llist, 6)->data);
  printlist(llist);

  printf("llist_set index: %d, value: 13, result: %d, len: %d\n", 6,
         llist_set(llist, 6, 13), llist_getlen(llist));
  printlist(llist);

  printf("llist_add index: %d, value: 666, result: %d, len: %d\n", 6,
         llist_add(llist, 6, llist_node_new(666)), llist_getlen(llist));
  printlist(llist);

  llist_destroy(&llist);
  printlist(llist);
  return 0;
}

int run_alist_tasks() {
  alist_node_t *alist = NULL;

  for (int i = 0; i < ARR_LEN; i++) {
    int kascii = i + 97;
    int vascii = i + 65;
    char *key = (char *)&kascii;
    char *val = (char *)&vascii;
    alist_node_t *node = alist_add(&alist, key, val);
    printf("alist_add key: %s, val: %s, len: %d\n", node->key, node->value,
           alist_getlen(alist));
    // printf("alist_get key: %s, val: %s\n", key, alist_get(alist,
    // key)->value);
  }

  return 0;
}