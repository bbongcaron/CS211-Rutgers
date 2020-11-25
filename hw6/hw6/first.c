#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
bool isPowerOf2(int num);
bool isInt(char* num);
bool isLegit(char* cacheSize, char* associativity, char* replacePolicy, char* blockSize);
void directCache(int cacheSize, int blockSize, char* replacePolicy, FILE* traceFile);

int main(int argc, char* argv[])
{
  if (!isLegit(argv[1], argv[2], argv[3], argv[4]))
  {
    printf("error\n");
    return 0;
  }
  int cacheSize = atoi(argv[1]);
  char* associativity = argv[2];
  char* replacePolicy = argv[3];
  int blockSize = atoi(argv[4]);
  FILE* traceFile = fopen(argv[5], "r");


  if (strcmp(associativity, "direct") == 0)
  {
    directCache(cacheSize, blockSize, replacePolicy, traceFile);
  }
  else if (strcmp(associativity, "assoc") == 0)
  {

  }
  else
  {

  }
  fclose(traceFile);
  return 0;
}

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

bool isLegit(char* cacheSize, char* associativity, char* replacePolicy, char* blockSize)
{
  if (!isInt(cacheSize) || !isInt(blockSize))
  {
    return false;
  }
  if (!isPowerOf2(atoi(cacheSize)) || !isPowerOf2(atoi(blockSize)))
  {
    return false;
  }
  //printf("cacheSize = %s is legit.\n", cacheSize);
  //printf("blockSize = %s is legit.\n", blockSize);
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

void directCache(int cacheSize, int blockSize, char* replacePolicy, FILE* traceFile)
{
  // 12 bytes (48-bit) memory addresses

  int linesPerSet = 1; //property of directCache
  int numSets = (cacheSize) / (linesPerSet*blockSize);
  int setBits = log10(numSets) / log10(2);
  int dataBits = log10(blockSize) / log10(2);
  int tagBits = 48 - setBits - dataBits;
  // Initialize the cache
  int** cache = malloc(sizeof(int*)*numSets);
  for (int i = 0; i < numSets; i++)
  {
    cache[i] = malloc(sizeof(int)*48);
  }

  int programCount = 0;
  char action = '\0';
  int cacheData = 0;
  while (fscanf(traceFile, "%X: %c %X", &programCount, &action, &cacheData))
  {
    //printf("0x%X: %c 0x%X\n", programCount, action, cacheData);
    if (action == 'R')
    {

    }
    else // action == 'W'
    {

    }
  }
  //printf("#EOF\n");

}
