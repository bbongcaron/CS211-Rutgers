#include <stdio.h>
#include <stdlib.h>

int numNodes = 0;

typedef struct Node
{
    int data;
    struct Node* next;

} Node;

void insert(Node** head, int newData)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->data = newData;

    Node* ptr = *head;
    Node* prev = NULL;
    while (ptr && ptr->data < newData)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if (!prev)
    {
      newNode->next = *head;
      *head = newNode;
    }
    else
    {
      newNode->next = ptr;
      prev->next = newNode;
    }
    numNodes++;
}

void delete(Node** head, int target)
{
  if (numNodes == 0)
  {
    return;
  }
  Node* ptr = *head;
  Node* prev = NULL;
  while(ptr && ptr->data != target)
  {
    prev = ptr;
    ptr = ptr->next;
  }
  if(!prev)
  {
    prev = ptr;
    ptr = ptr->next;
    free(prev);
    // CHANGE HEAD TO POINT TO THE NEW NODE THAT PTR IS POINTING TO
    *head = ptr;
  }
  else if (!ptr) {
    return;
  }
  else
  {
    prev->next = ptr->next;
    free(ptr);
  }

  numNodes--;
}

int isPrinted(int printed[], int newData)
{
  for(int i = 0; i < numNodes; i++)
  {
    if (printed[i] == newData)
    {
      return 1;
    }
  }
  return 0;
}

void printNode(Node** head)
{
    Node* first = *head;
    Node* ptr;
    int* printed = malloc(sizeof(int)*numNodes);
    int numPrinted = 0;
    while (first)
    {
        ptr = first;
        first = first->next;
        if (isPrinted(printed, ptr->data) == 0)
        {
          printf("%d\t", ptr->data);
          printed[numPrinted] = ptr->data;
          numPrinted++;
        }
        free(ptr);
    }
    free(printed);
    printf("\n");
    *head = NULL;
}

int main(int argc, char* argv[argc+1])
{
    Node* head = NULL;
    FILE* in_file = fopen(argv[1], "r");
    char action;
    int data;
    while (fscanf(in_file, "%c\t%d\n", &action, &data) != EOF) {
      switch (action) {
        case 'i':
        insert(&head, data);
        break;
        case 'd':
        delete(&head, data);
        break;
      }
    }

    printf("%d\n", numNodes);
    printNode(&head);
    return EXIT_SUCCESS;
}
