#include "quick.h"
#include <ceduc/util/sort.h>

void sort_quick(int arr[], int low, int high) {
  if (low < high) {
    int p = qsort_partition(arr, low, high);
    sort_quick(arr, low, p - 1);
    sort_quick(arr, p + 1, high);
  }
}

int qsort_partition(int arr[], int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j <= high - 1; j++) {
    if (arr[j] <= pivot) {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }

  i++;
  swap(&arr[i], &arr[high]);
  return i;
}