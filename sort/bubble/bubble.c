#include <ceduc/util/fmt.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fillarr(int[], int len);
void sortarr(int[], int len);
void swap(int *, int *);

int main() {
  int arr[13] = {};
  int len = sizeof(arr) / sizeof(int);
  printarr(arr, len);
  fillarr(arr, len);
  printarr(arr, len);
  sortarr(arr, len);
  printarr(arr, len);
  return 0;
}

void fillarr(int arr[], int len) {
  srand(time(NULL));
  for (int i = 0; i < len; i++) {
    arr[i] = rand() % 100;
  }
}

void swap(int *a, int *b) {
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

void sortarr(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len - i; j++) {
      if (arr[j] > arr[j + 1]) {
        swap(&arr[j], &arr[j + 1]);
      }
    }
  }
}