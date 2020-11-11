#include <stdio.h>
#include <stdlib.h>

int numBits(unsigned short x)
{
  int length = 0;
  while (x > 0)
  {
    x = x >> 1;
    length++;
  }
  return length;
}

int get(unsigned short x, int n)
{
  if ((x & (1 << n)) == 0)
  {
    return 0;
  }
  return 1;
}

int main(int argc, char* argv[])
{
  unsigned short x = (unsigned short)atoi(argv[1]);
  int numPairs = 0;
  int numOnes = 0;
  int length = numBits(x);
  for (int i = 0; i < length - 1; i++)
  {
    if (get(x, i) == 1 && get(x, i + 1) == 1)
    {
      numPairs++;
      i++;
    }
  }
  for (int i = 0; i < length; i++)
  {
    if (get(x, i) == 1)
    {
      numOnes++;
    }
  }
  if (numOnes % 2 == 0)
  {
    printf("%s\t", "Even-Parity");
  }
  else
  {
    printf("%s\t", "Odd-Parity");
  }
  printf("%d\n", numPairs);
  return 0;
}
