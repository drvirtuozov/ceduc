void sort_insertion(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    int j = i - 1;
    int tmp = arr[i];

    while (j >= 0 && arr[j] > tmp) {
      arr[j + 1] = arr[j];
      j--;
    }

    arr[j + 1] = tmp;
  }
}