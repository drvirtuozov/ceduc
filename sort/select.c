#include <ceduc/util/sort.h>

void sort_selection(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    int min = arr[i];

    for (int j = i; j < len; j++) {
      if (arr[j] <= min) {
        min = arr[j];
        swap(&arr[i], &arr[j]);
      }
    }
  }
}