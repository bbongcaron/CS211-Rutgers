#include <stdio.h>
#include <stdlib.h>

int get(unsigned short x, int n)
{
  if ((x & (1 << n)) == 0)
  {
    return 0;
  }
  return 1;
}

void set(unsigned short* x, int n, int v)
{
  if (v == 0)
  {
    // the complement of 1 << n would result in every bit except the nth bit
    // being 1 and the nth bit being 0
    //printf("n = %hd\n", n);
    unsigned int bitSetter = ~(1 << n);
    //printf("%hd\n", bitSetter);
    *x = *x & bitSetter;
  }
  else if (v == 1)
  {
    // every bit except the nth bit is 0; nth bit is 1
    unsigned int bitSetter = 1 << n;
    *x = *x | bitSetter;
  }
}

int main(int argc, char* argv[])
{
    unsigned short x = (short)atoi(argv[1]);
    unsigned short num1;
    unsigned short num2;
    for (int i = 0; i < 16; i++)
    {
      set(&num1, i, get(x, i));
      set(&num2, i, get(x, 15 - i));
    }
    if ((num1 & num2) == x)
    {
      printf("Is-Palindrome\n");
    }
    else
    {
      printf("Not-Palindrome\n");
    }
    return EXIT_SUCCESS;
}
