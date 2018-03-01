#include <ceduc/data/dynarr.h>
#include <ceduc/sort/bubble.h>
#include <ceduc/util/fmt.h>
#include <ceduc/util/sort.h>
#include <stdio.h>
#include <stdlib.h>

#define ARR_LEN 13

int main(int argc, char *argv[]) {
  dynarr_t *da = dynarr_new();

  if (da == NULL) {
    printf("failed to create a dynarr\n");
    return 1;
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("pushing to array...\n");
    unsigned int len = dynarr_push(&da, i);
    // printf("\n(len:%d) %s\n", len, dynarr_string(arr));
    printarr(da->arr, da->len);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("shifting from array...\n");
    unsigned int len = dynarr_shift(da);
    // printf("\n(len:%d) %s\n", len, dynarr_string(arr));
    printarr(da->arr, da->len);
  }

  for (int i = 0; i < ARR_LEN; i++) {
    printf("unshifting to array...\n");
    unsigned int len = dynarr_unshift(&da, i);
    // printf("\n(len:%d) %s\n", len, dynarr_string(arr));
    printarr(da->arr, da->len);
  }

  printf("bubble sorting array...\n");
  sort_bubble(da->arr, da->len);
  printarr(da->arr, da->len);

  printf("index: %d, value: %d\n", 666, dynarr_get(da, 666));

  printf("setting index: 19, value: 19, len: %d, cap: %d\n",
         dynarr_set(da, 19, 19), da->cap);
  printarr(da->arr, da->len);

  return 0;
}
