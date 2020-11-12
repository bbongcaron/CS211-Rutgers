#include "io.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int je(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      return 1;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (ax == bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (ax == cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (ax == dx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (ax == atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (bx == ax)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      return 1;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (bx == cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (bx == dx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (bx == atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (cx == ax)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (cx == bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      return 1;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (cx == dx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (cx == atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (dx == ax)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (dx == bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (dx == cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      return 1;
    }
    else
    {
      if (dx == atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else
  {
    return -1;
  }
}
int jne(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (ax != bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (ax != cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (ax != dx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (ax != atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (bx != ax)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (bx != cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (bx != dx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (bx != atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (cx != ax)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (cx != bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (cx != dx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (cx != atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (dx != ax)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (dx != bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (dx != cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      return 0;
    }
    else
    {
      if (dx != atoi(x))
      {
        return 1;
      }
      return 0;
    }
  }
  else
  {
    return -1;
  }
}
int jg(char* x, char* y)
{
  if (strcmp(y, "ax") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (bx > ax)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (cx > ax)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (dx > ax)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (atoi(x) > ax)
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "bx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (ax > bx)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (cx > bx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (dx > bx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (atoi(x) > bx)
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "cx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (ax > cx)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (bx > cx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      if (dx > cx)
      {
        return 1;
      }
      return 0;
    }
    else
    {
      if (atoi(x) > cx)
      {
        return 1;
      }
      return 0;
    }
  }
  else if (strcmp(y, "dx") == 0)
  {
    if (strcmp(x, "ax") == 0)
    {
      if (ax > dx)
      {
        return 1;
      }
      return 0;
    }
    if (strcmp(x, "bx") == 0)
    {
      if (bx > dx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "cx") == 0)
    {
      if (cx > dx)
      {
        return 1;
      }
      return 0;
    }
    else if (strcmp(x, "dx") == 0)
    {
      return 0;
    }
    else
    {
      if (atoi(x) > dx)
      {
        return 1;
      }
      return 0;
    }
  }
  else
  {
    return -1;
  }
}
//int jge(char* x, char* y);
//int jl(char* x, char* y);
//int jle(char* x, char* y);
