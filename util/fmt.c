#include <ceduc/data/llist.h>
#include <stdio.h>

void printarr(int arr[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%d ", arr[i]);
  }

  printf("\n");
}

void printlist(llist_node_t *head) {
  llist_node_t *temp = head;
  printf("%d ", head->data);

  while (temp->next != NULL) {
    temp = temp->next;
    printf("%d ", temp->data);
  }

  printf("\n");
}