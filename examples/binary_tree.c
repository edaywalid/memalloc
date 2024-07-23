#include "../memalloc.h"
#include <stdio.h>

typedef struct Node *tree;
typedef struct Node {
  int val;
  tree right;
  tree left;
} Node;

tree insert(tree *root, int val) {
  if (!(*root)) {
    *root = malloc(sizeof(Node));
    (*root)->val = val;
    (*root)->right = NULL;
    (*root)->left = NULL;

    return *root;
  }

  if ((*root)->val < val) {
    return insert(&(*root)->right, val);
  } else if ((*root)->val > val) {
    return insert(&(*root)->left, val);
  }
  return *root;
}

void print_tree(tree root) {
  if (!root) {
    return;
  }

  print_tree(root->left);
  printf("%d\n", root->val);
  print_tree(root->right);
}

tree find_min(tree root) {
  while (root->left != NULL) {
    root = root->left;
  }
  return root;
}

void delete_item(tree *root, int val) {
  if (!(*root)) {
    return;
  }

  if (val < (*root)->val) {
    delete_item(&(*root)->left, val);
  } else if (val > (*root)->val) {
    delete_item(&(*root)->right, val);
  } else {
    if ((*root)->left == NULL) {
      tree temp = (*root)->right;
      free(*root);
      *root = temp;
    } else if ((*root)->right == NULL) {
      tree temp = (*root)->left;
      free(*root);
      *root = temp;
    } else {
      tree temp = find_min((*root)->right);
      (*root)->val = temp->val;
      delete_item(&(*root)->right, temp->val);
    }
  }
}
int main() {
  tree root = NULL;
  insert(&root, 10);
  insert(&root, 5);
  insert(&root, 15);
  insert(&root, 3);
  insert(&root, 7);
  insert(&root, 12);
  insert(&root, 17);
  insert(&root, 1);
  insert(&root, 4);
  insert(&root, 6);
  insert(&root, 8);
  insert(&root, 11);
  insert(&root, 13);
  insert(&root, 16);
  insert(&root, 18);
  print_tree(root);
  printf("\n");
  delete_item(&root, 10);
  print_tree(root);
  return 0;
}
