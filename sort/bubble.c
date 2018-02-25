#include <ceduc/sort/bubble.h>
#include <ceduc/util/fmt.h>
#include <ceduc/util/sort.h>

void sort_bubble(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}