#include <ceduc/data/alist.h>
#include <ceduc/data/dynarr.h>
#include <ceduc/data/llist.h>
#include <ceduc/sort/bubble.h>
#include <ceduc/sort/insert.h>
#include <ceduc/sort/quick.h>
#include <ceduc/sort/select.h>
#include <ceduc/util/fmt.h>
#include <ceduc/util/sort.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

#define ARR_LEN 13

int run_sort_tasks();
int run_dynarr_tasks();
int run_llist_tasks();
int run_alist_tasks();

int main(int argc, char *argv[]) {
  int err = 0;

  err = run_sort_tasks();

  if (err != 0) {
    return err;
  }

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

int run_sort_tasks() {
  int arr[ARR_LEN];

  fillarr(arr, ARR_LEN);
  printarr(arr, ARR_LEN);
  printf("sort_bubble...\n");
  sort_bubble(arr, ARR_LEN);
  printarr(arr, ARR_LEN);

  printf("\n");

  fillarr(arr, ARR_LEN);
  printarr(arr, ARR_LEN);
  printf("sort_selection...\n");
  sort_selection(arr, ARR_LEN);
  printarr(arr, ARR_LEN);

  printf("\n");

  fillarr(arr, ARR_LEN);
  printarr(arr, ARR_LEN);
  printf("sort_insertion...\n");
  sort_insertion(arr, ARR_LEN);
  printarr(arr, ARR_LEN);

  printf("\n");

  fillarr(arr, ARR_LEN);
  printarr(arr, ARR_LEN);
  printf("sort_quick...\n");
  sort_quick(arr, 0, ARR_LEN - 1);
  printarr(arr, ARR_LEN);

  printf("\n");
  return 0;
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
  setlocale(LC_ALL, "");
  alist_node_t *alist = NULL;

  for (int i = 0; i < ARR_LEN; i++) {
    static wchar_t key[] = L"а";
    static wchar_t val[] = L"А";
    alist_add(&alist, key, val);
    printf("alist_add key: %ls, val: %ls, len: %d\n", key, val,
           alist_getlen(alist));
    (*key)++;
    (*val)++;
  }

  for (int i = 0; i < ARR_LEN; i++) {
    static wchar_t key[] = L"а";
    printf("alist_get key: %ls, val: %ls\n", key, alist_get(alist, key)->value);
    (*key)++;
  }

  wchar_t *key = L"б";
  printf("get key: %ls, got value: %ls\n", key,
         alist_delete(&alist, key)->value);
  wchar_t *key2 = L"а";
  printf("get key: %ls, got value: %ls\n", key2, alist_get(alist, key2)->value);
  wchar_t *key3 = L"в";
  printf("get key: %ls, got value: %ls\n", key3, alist_get(alist, key3)->value);
  printf("get key: %ls, got value: %p\n", key, alist_get(alist, key));
  alist_destroy(&alist);
  return 0;
}