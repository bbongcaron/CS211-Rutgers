#include "io.h"
#include "arithmetic.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void add(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "bx") == 0)
    {
      ax += bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      ax += cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      ax += dx;
    }
    else
    {
      ax += atoi(x);
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      bx += ax;
    }
    else if (strcmp(x, "cx") == 0)
    {
      bx += cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      bx += dx;
    }
    else
    {
      bx += atoi(x);
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      cx += ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      cx += bx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      cx += dx;
    }
    else
    {
      cx += atoi(x);
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      dx += ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      dx += bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      dx += cx;
    }
    else
    {
      dx += atoi(x);
    }
  }
  else
  {
    printf("Error in add(x,y). y must be a register.\n");
  }
  return;
}

void sub(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "bx") == 0)
    {
      ax -= bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      ax -= cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      ax -= dx;
    }
    else
    {
      ax -= atoi(x);
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      bx -= ax;
    }
    else if (strcmp(x, "cx") == 0)
    {
      bx -= cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      bx -= dx;
    }
    else
    {
      bx -= atoi(x);
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      cx -= ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      cx -= bx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      cx -= dx;
    }
    else
    {
      cx -= atoi(x);
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      dx -= ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      dx -= bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      dx -= cx;
    }
    else
    {
      dx -= atoi(x);
    }
  }
  else
  {
    printf("Error in sub(x,y). y must be a register.\n");
  }
  return;
}

void mul(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "bx") == 0)
    {
      ax *= bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      ax *= cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      ax *= dx;
    }
    else
    {
      ax *= atoi(x);
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      bx *= ax;
    }
    else if (strcmp(x, "cx") == 0)
    {
      bx *= cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      bx *= dx;
    }
    else
    {
      bx *= atoi(x);
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      cx *= ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      cx *= bx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      cx *= dx;
    }
    else
    {
      cx *= atoi(x);
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      dx *= ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      dx *= bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      dx *= cx;
    }
    else
    {
      dx *= atoi(x);
    }
  }
  else
  {
    printf("Error in mul(x,y). y must be a register.\n");
  }
  return;
}

void divide(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "bx") == 0)
    {
      ax /= bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      ax /= cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      ax /= dx;
    }
    else
    {
      ax /= atoi(x);
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      bx /= ax;
    }
    else if (strcmp(x, "cx") == 0)
    {
      bx /= cx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      bx /= dx;
    }
    else
    {
      bx /= atoi(x);
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      cx /= ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      cx /= bx;
    }
    else if (strcmp(x, "dx") == 0)
    {
      cx /= dx;
    }
    else
    {
      cx /= atoi(x);
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      dx /= ax;
    }
    else if (strcmp(x, "bx") == 0)
    {
      dx /= bx;
    }
    else if (strcmp(x, "cx") == 0)
    {
      dx /= cx;
    }
    else
    {
      dx /= atoi(x);
    }
  }
  else
  {
    printf("Error in divide(x,y). y must be a register.\n");
  }
  return;
}
