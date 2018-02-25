#include <stdlib.h>
#include <time.h>

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