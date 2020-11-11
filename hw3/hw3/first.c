#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void set(unsigned int* x, unsigned int n, int v)
{
  if (v == 0)
  {
    // the complement of 1 << n would result in every bit except the nth bit
    // being 1 and the nth bit being 0
    //printf("n = %hd\n", n);
    unsigned int bitSetter = ~(1 << n);
    //printf("%hd\n", bitSetter);
    *x = *x & bitSetter;
    printf("%u\n", *x);
  }
  else if (v == 1)
  {
    // every bit except the nth bit is 0; nth bit is 1
    unsigned int bitSetter = 1 << n;
    *x = *x | bitSetter;
    printf("%u\n", *x);
  }
}

int get(unsigned int x, int n)
{
  if ((x & (1 << n)) == 0)
  {
    return 0;
  }
  return 1;
}

void comp(unsigned int* x, int n)
{
  if (get(*x, n) == 0)
  {
    set(x, n, 1);
  }
  else
  {
    set(x, n, 0);
  }
}

int main(int argc, char* argv[])
{
  FILE* in_file = fopen(argv[1], "r");
  unsigned int x;
  char action[5] = "null"; unsigned int n; int v;
  fscanf(in_file, "%u\n", &x);
  while (fscanf(in_file, "%s\t%u\t%d\n", action, &n, &v) != EOF)
  {
    if (strcmp(action, "get") == 0)
    {
      printf("%d\n", get(x, n));
    }
    else if (strcmp(action, "comp") == 0)
    {
      comp(&x, n);
    }
    else if (strcmp(action, "set") == 0)
    {
      set(&x, n, v);
    }
  }
  fclose(in_file);
  return EXIT_SUCCESS;
}
