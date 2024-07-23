#include "../memalloc.h"
#include <stdio.h>

typedef struct Node *list;
typedef struct Node {
  int val;
  list next;
} Node;

list push(list *root, int val) {
  list new_node = (list)malloc(sizeof(Node));
  new_node->val = val;
  new_node->next = *root;
  *root = new_node;
  return new_node;
}

int pop(list *root) {
  if (root == NULL) {
    return -1;
  }
  int val = (*root)->val;
  list tmp = *root;
  *root = (*root)->next;
  free(tmp);
  return val;
}
void print_list(list root) {
  while (root) {
    printf("%d ", root->val);
    root = root->next;
  }
  printf("\n");
}

list init() { return NULL; }
int main() {
  list head = init();
  head = push(&head, 5);
  head = push(&head, 3);

  print_list(head);
}
