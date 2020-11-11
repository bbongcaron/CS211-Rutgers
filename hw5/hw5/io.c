#include "io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void read(char* x)
{
  if (strcmp(x, "ax") == 0)
  {
    scanf("%hi", &ax);
  }
  else if (strcmp(x, "bx") == 0)
  {
    scanf("%hi", &bx);
  }
  else if (strcmp(x, "cx") == 0)
  {
    scanf("%hi", &cx);
  }
  else if (strcmp(x, "dx") == 0)
  {
    scanf("%hi", &dx);
  }
  return;
}

void print(char* x)
{
  if (strcmp(x, "ax") == 0)
  {
    printf("%hi", ax);
  }
  else if (strcmp(x, "bx") == 0)
  {
    printf("%hi", bx);
  }
  else if (strcmp(x, "cx") == 0)
  {
    printf("%hi", cx);
  }
  else if (strcmp(x, "dx") == 0)
  {
    printf("%hi", dx);
  }
  else
  {
    printf("%hi", *x);
  }
  return;
}
