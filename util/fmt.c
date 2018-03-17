#include <ceduc/data/llist.h>
#include <stdio.h>

void printarr(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }

  printf("\n");
}

void printlist(llist_node_t *head) {
  head = llist_gethead(head);

  if (head != NULL) {
    printf("%d ", head->data);

    while (head->next != NULL) {
      head = head->next;
      printf("%d ", head->data);
    }
  }

  printf("\n");
}