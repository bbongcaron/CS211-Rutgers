#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node* left;
  struct Node* right;
} Node;

void insert(Node** bst, int newData)
{
  if (!*bst)
  {
      Node* newNode = malloc(sizeof(Node));
      newNode->data = newData;
      /* NEED TO INITIALIZE EMPTY NODES ON LEFT AND RIGHT */
      newNode->left = NULL;
      newNode->right = NULL;
      *bst = newNode;
      return;
  }

  Node* prev = NULL;
  Node* ptr = *bst;
  while (ptr)
  {
    prev = ptr;
    if (newData == ptr->data){
      return;
    }
    else if (newData < ptr->data)
    {
      ptr = ptr->left;
    }
    else
    {
      ptr = ptr->right;
    }
  }
  if (newData < prev->data)
  {
    prev->left = malloc(sizeof(Node));
    prev->left->data = newData;
    prev->left->left = NULL;
    prev->left->right = NULL;
  }
  else
  {
    prev->right = malloc(sizeof(Node));
    prev->right->data = newData;
    prev->right->left = NULL;
    prev->right->right = NULL;
  }
}

void print(Node** node)
{
  if(!(*node))
  {
    return;
  }
  print(&((*node)->left));
  printf("%d\t", (*node)->data);
  print(&((*node)->right));
  free(*node);
}

int main(int argc, char* argv[])
{
  Node* bst = NULL;
  FILE* in_file = fopen(argv[1], "r");
  int data;
  while (fscanf(in_file, "i\t%d\n", &data) != EOF)
  {
    insert(&bst, data);
  }
  print(&bst);
  printf("\n");
}
