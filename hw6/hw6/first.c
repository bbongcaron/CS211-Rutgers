#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

bool isPowerOf2(int num)
{
  while (num > 1)
  {
    if (num % 2 == 0)
    {
      num /= 2;
    }
    else
    {
      return false;
    }
  }
  return true;
}

bool isInt(char* num)
{
  for (int i = 0; i < strlen(num); i++)
  {
    if (!isdigit(num[i]))
    {
      return false;
    }
  }
  return true;
}
bool isLegit(int cacheSize, char* associativity, char* replacePolicy, int blockSize)
{
  if (!isPowerOf2(cacheSize) || !isPowerOf2(blockSize))
  {
    return false;
  }
  //printf("cacheSize = %d is legit.\n", cacheSize);
  //printf("blockSize = %d is legit.\n", blockSize);
  if (strcmp(replacePolicy, "lru") != 0 && strcmp(replacePolicy, "fifo") != 0)
  {
    return false;
  }
  //printf("replacePolicy = %s is legit.\n", replacePolicy);
  char temp[20] = "\0";
  strcpy(temp, associativity);
  if (strcmp(associativity, "direct") != 0 && strcmp(associativity, "assoc") != 0)
  {
    char* token = strtok(temp, ":");
    if(strcmp(token, "assoc") != 0)
    {
      return false;
    }
    else
    {
      token = strtok(NULL, ":");
      if(!isInt(token) || !isPowerOf2(atoi(token)))
      {
        return false;
      }
    }
  }
  //printf("associativity = %s is legit.\n", associativity);
  return true;
}

int main(int argc, char* argv[])
{
  if (!isInt(argv[1]) || !isInt(argv[4]))
  {
    printf("error\n");
    return 0;
  }
  int cacheSize = atoi(argv[1]);
  char* associativity = argv[2];
  char* replacePolicy = argv[3];
  int blockSize = atoi(argv[4]);
  FILE* traceFile = fopen(argv[5], 'r');

  if (!isLegit(cacheSize, associativity, replacePolicy, blockSize))
  {
    printf("error\n");
    return 0;
  }
}
