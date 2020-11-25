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
int getBit(int x, int n);
void setBit(int* x, int n, int v);

int memReads = 0;
int memWrites = 0;
int cacheHits = 0;
int cacheMiss = 0;

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

int getBit(int x, int n)
{
  if ((x & (1 << n)) == 0)
  {
    return 0;
  }
  return 1;
}

void setBit(int* x, int n, int v)
{
  if (v == 0)
  {
    // the complement of 1 << n would result in every bit except the nth bit
    // being 1 and the nth bit being 0
    //printf("n = %hd\n", n);
    int bitSetter = ~(1 << n);
    //printf("%hd\n", bitSetter);
    *x = *x & bitSetter;
  }
  else if (v == 1)
  {
    // every bit except the nth bit is 0; nth bit is 1
    int bitSetter = 1 << n;
    *x = *x | bitSetter;
  }
}

void printBits(int x, int length)
{
  for (int i = length - 1; i >= 0; i--)
  {
    printf("%d", getBit(x, i));
  }
  printf(" = %d\n", x);
}

void freeCache(int*** cache, int numSets, int linesPerSet)
{
  for (int i = 0; i < numSets; i++)
  {
    for (int j = 0; j < linesPerSet; j++)
    {
      free(cache[i][j]);
    }
    free(cache[i]);
  }
  free(cache);
}
void directCache(int cacheSize, int blockSize, char* replacePolicy, FILE* traceFile)
{
  // 12 bytes (48-bit) memory addresses
  // 1 LINE PER SET IN A DIRECT CACHE
  int linesPerSet = 1; //property of directCache
  int numSets = (cacheSize) / (linesPerSet*blockSize);
  int setBits = log10(numSets) / log10(2);
  int dataBits = log10(blockSize) / log10(2);
  int tagBits = 48 - setBits - dataBits;
  /*
    Initialize Cache
  */
  int*** cache = malloc(sizeof(int**)*numSets);
  for (int i = 0; i < numSets; i++)
  {
    cache[i] = malloc(sizeof(int*)*linesPerSet);
    for (int j = 0; j < linesPerSet; j++)
    {
      // cache[i][j][0] is the valid bit in set i, line j
      // cache[i][j][1] is the tag in set i, line j
      // cache[i][j][2] is the data in set i, line j
      cache[i][j] = malloc(sizeof(int)*3);
      cache[i][j][0] = 0;  //cache starts cold
    }
  }
  int programCount = 0;
  char action = '\0';
  int cacheData = 0;
  while (fscanf(traceFile, "%X: %c %X", &programCount, &action, &cacheData))
  {
    // printf("0x%X: %c 0x%X\n", programCount, action, cacheData);
    // string representation of cacheData
    // length shows the length up to which the rest of tag is all zeros
    char hexString[13] = "\0";
    sprintf(hexString, "%X", cacheData);
    /* Get the set # that the data will be stored in */
    int setIndex = 0;
    for (int i = dataBits; i <= 47 - tagBits; i++)
    {
      setBit(&setIndex, i - dataBits, getBit(cacheData, i));
    }
    /* Get the tag of the data */
    int tag = 0;
    for (int i = dataBits + setBits; i < 4*strlen(hexString); i++)
    {
      setBit(&tag, i - dataBits - setBits, getBit(cacheData, i));
    }
    //printf("tag of %x : \t", cacheData);
    //printBits(tag, 4*strlen(hexString));
    if (action == 'R')
    {
      for (int i = 0; i < linesPerSet; i++)
      {
        if (cache[setIndex][i][0] == 1)
        {
          if (cache[setIndex][i][1] == tag)
          {
            cacheHits++;
          }
        }
        else // cache[setIndex][i][0] == 0
        {
          cacheMiss++;
          cache[setIndex][i][0] = 1;
          cache[setIndex][i][1] = tag;
        }
      }
    }
    else // action == 'W'
    {

    }
  }

  freeCache(cache, numSets, linesPerSet);
}
