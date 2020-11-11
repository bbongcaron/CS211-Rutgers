#include "io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void read(char* x)
{
  if (strcmp(x, "ax") == 0)
  {
    scanf("%d", &ax);
  }
  else if (strcmp(x, "bx") == 0)
  {
    scanf("%d", &bx);
  }
  else if (strcmp(x, "cx") == 0)
  {
    scanf("%d", &cx);
  }
  else if (strcmp(x, "dx") == 0)
  {
    scanf("%d", &dx);
  }
  return;
}

void print(char* x)
{
  if (strcmp(x, "ax") == 0)
  {
    printf("%d", ax);
  }
  else if (strcmp(x, "bx") == 0)
  {
    printf("%d", bx);
  }
  else if (strcmp(x, "cx") == 0)
  {
    printf("%d", cx);
  }
  else if (strcmp(x, "dx") == 0)
  {
    printf("%d", dx);
  }
  else
  {
    printf("%d", *x);
  }
  return;
}
