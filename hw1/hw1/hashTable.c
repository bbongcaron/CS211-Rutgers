#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
  int data;
  struct Node* next;

}Node;

int numCollisions = 0;
int searchSuccesses = 0;

int hashFxn(int data)
{
  if (data < 0)
  {
    return (data % 10000) + 10000;
  }
  return data % 10000;
}

void hash(Node* hashtable[], int data)
{
  int key = hashFxn(data);
  Node* newNode = malloc(sizeof(Node));
  newNode->data = data;
  if (hashtable[key]->next)
  {
    numCollisions++;
  }
  newNode->next = hashtable[key]->next;
  hashtable[key]->next = newNode;
}

int search(Node* hashtable[], int target)
{
  for (int i = 0; i < 10000; i++)
  {
    Node* ptr = hashtable[i]->next;
    while (ptr)
    {
      if (ptr->data == target)
      {
        return 1;
      }
      ptr = ptr->next;
    }
  }
  return 0;
}

void clean(Node* hashtable[], int i)
{
  if (!hashtable[i]->next){
      free(hashtable[i]);
  }
  else
  {
    Node* prev = NULL;
    Node* ptr = hashtable[i]->next;
    while(ptr)
    {
      prev = ptr;
      ptr = ptr->next;
      free(prev);
    }
    free(hashtable[i]);
  }
}

int main(int argc, char* argv[])
{
  Node* hashtable[10000];
  /* Need to initialize hashtable with NULL pointers */
  for (int i = 0; i < 10000; i++){
    hashtable[i] = malloc(sizeof(Node));
    hashtable[i]->next = NULL;
  }
  FILE* in_file = fopen(argv[1], "r");
  char action;
  int data;
  while (fscanf(in_file, "%c\t%d\n", &action, &data) != EOF)
  {
    switch (action) {
      case 'i':
      if (search(hashtable, data) == 0){
        hash(hashtable, data);
      }
      else
      {
        numCollisions++;
      }
      break;
      case 's':
      if (search(hashtable, data) == 1)
      {
        searchSuccesses++;
      }
      break;
    }
  }
  printf("%d\n", numCollisions);
  printf("%d\n", searchSuccesses);

  for (int i = 0; i < 10000; i++){
    clean(hashtable, i);
  }

  return EXIT_SUCCESS;

}
