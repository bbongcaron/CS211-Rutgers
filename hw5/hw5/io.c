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
    printf("%hi", atoi(x));
  }
  return;
}

void move(char* x, char* y)
{
  /* Copy x to y. This leaves x unchanged. */
  /* Note: y must be a register */
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "bx") == 0)
    {
      ax = bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      ax = cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      ax = dx;
    }
    else
    {
      ax = atoi(x);
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      bx = ax;
    }
    else if (strcmp(x, "cx") == 0)
    {
      bx = cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      bx = dx;
    }
    else
    {
      bx = atoi(x);
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      cx = ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      cx = bx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      cx = dx;
    }
    else
    {
      cx = atoi(x);
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      dx = ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      dx = bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      dx = cx;
    }
    else
    {
      dx = atoi(x);
    }
  }
  else
  {
    printf("Error in move(x,y). y must be a register.\n");
  }
  return;

}
