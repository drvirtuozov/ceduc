#include <ceduc/util/sort.h>

void sort_insertion(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    for (int j = len - 1; j > i; j--) {
      if (arr[j - 1] > arr[j]) {
        swap(&arr[j - 1], &arr[j]);
      }
    }
  }
}