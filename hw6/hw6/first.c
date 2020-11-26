#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

bool isLegit(char* cacheSize, char* associativity, char* replacePolicy, char* blockSize);
void simulateCache(int cacheSize, int blockSize, char* replacePolicy, FILE* traceFile, char* associativity);

int memReads = 0;
int memWrites = 0;
int cacheHits = 0;
int cacheMiss = 0;

typedef struct Line
{
  bool isValid;
  size_t tag;
  int data;
}Line;

typedef struct Set
{
  int numValidLines;
  Line* line;
  int* lfu;
  int fifo;
}Set;

typedef struct Cache{
  int numSets;
  int linesPerSet;
  Set* set;
}Cache;

int main(int argc, char* argv[])
{
  if (argc != 6 || !isLegit(argv[1], argv[2], argv[3], argv[4]))
  {
    printf("error\n");
    return 0;
  }
  int cacheSize = atoi(argv[1]);
  char* associativity = argv[2];
  char* replacePolicy = argv[3];
  int blockSize = atoi(argv[4]);
  FILE* traceFile = fopen(argv[5], "r");

  simulateCache(cacheSize, blockSize, replacePolicy, traceFile, associativity);

  printf("Memory reads: %d\n", memReads);
  printf("Memory writes: %d\n", memWrites);
  printf("Cache hits: %d\n", cacheHits);
  printf("Cache misses: %d\n", cacheMiss);
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

int getBit(size_t x, int n)
{
  if ((x & (1 << n)) == 0)
  {
    return 0;
  }
  return 1;
}

void setBit(size_t* x, int n, int v)
{
  if (v == 0)
  {
    // the complement of 1 << n would result in every bit except the nth bit
    // being 1 and the nth bit being 0
    //printf("n = %hd\n", n);
    size_t bitSetter = ~(1 << n);
    //printf("%hd\n", bitSetter);
    *x = *x & bitSetter;
  }
  else if (v == 1)
  {
    // every bit except the nth bit is 0; nth bit is 1
    size_t bitSetter = 1 << n;
    *x = *x | bitSetter;
  }
}

void printBits(size_t x, int length)
{
  for (int i = length - 1; i >= 0; i--)
  {
    printf("%d", getBit(x, i));
  }
  printf(" = %lx\n", x);
}

void freeCache(Cache cache)
{
  for (int i = 0; i < cache.numSets; i++)
  {
    free(cache.set[i].lfu);
    free(cache.set[i].line);
  }
  free(cache.set);
}

Cache initializeCache(int numSets, int linesPerSet)
{
  Cache cache;
  cache.numSets = numSets;
  cache.linesPerSet = linesPerSet;
  cache.set = malloc(sizeof(Set)*numSets);
  for (int i = 0; i < numSets; i++)
  {
    cache.set[i].lfu = malloc(sizeof(int)*linesPerSet);
    for (int j = 0; j < linesPerSet; j++)
    {
      cache.set[i].lfu[j] = j;
    }
    cache.set[i].fifo = 0;
    cache.set[i].numValidLines = 0;
    cache.set[i].line = malloc(sizeof(Line)*linesPerSet);
    for (int j = 0; j < linesPerSet; j++)
    {
      cache.set[i].line[j].isValid = false;
      cache.set[i].line[j].tag = 0;
      cache.set[i].line[j].data = 0;
    }
  }
  return cache;
}

void deleteElement(int* array, int length, int target)
{
  for (int i = 0; i < length - 1; i++)
  {
    if (array[i] == target)
    {
      for (int j = i + 1; j < length; j++)
      {
        array[j-1] = array[j];
      }
      return;
    }
  }
}

void shiftLeft(int* array, int length)
{
  for (int i = 1; i < length; i++)
  {
    array[i-1] = array[i];
  }
}

void updateLRU(Cache* cache, bool isHit, int setIndex, size_t tag, int i)
{
  if (isHit)
  {
    deleteElement(cache->set[setIndex].lfu, cache->set[setIndex].numValidLines, i);
    cache->set[setIndex].lfu[cache->set[setIndex].numValidLines - 1] = i;
    cache->set[setIndex].line[cache->set[setIndex].numValidLines - 1].isValid = true;
    cache->set[setIndex].line[cache->set[setIndex].numValidLines - 1].tag = tag;
  }
  else // (!isHit)
  {
    // need to decide which line to evict
    // Check if there is room in the set before deciding to evict
    if (cache->set[setIndex].numValidLines < cache->linesPerSet)
    {
      // if a set still has not been completely filled with valid lines
      // update the lowest index free line
      cache->set[setIndex].line[cache->set[setIndex].numValidLines].isValid = true;
      cache->set[setIndex].line[cache->set[setIndex].numValidLines].tag = tag;
      // the lowest index free line is now the most recently used
      // Higher indexes mean more recently used
      cache->set[setIndex].lfu[cache->set[setIndex].numValidLines] = cache->set[setIndex].numValidLines;
      // now have an additional vaild line
      cache->set[setIndex].numValidLines++;
    }
    else // cache.set[setIndex].numValidLines >= linesPerSet
    {
      // get the index of the line to be replaced
      int replaceLine = cache->set[setIndex].lfu[0];
      // shift all elements of the lfu array to the left by 1
      shiftLeft(cache->set[setIndex].lfu, cache->linesPerSet);
      // the replaceLine is now the most recently used
      cache->set[setIndex].lfu[cache->linesPerSet - 1] = replaceLine;
      // update that line in cache
      cache->set[setIndex].line[replaceLine].isValid = true;
      cache->set[setIndex].line[replaceLine].tag = tag;
    }
  }
}

void updateFIFO(Cache* cache, int setIndex, size_t tag)
{
  cache->set[setIndex].line[cache->set[setIndex].fifo].tag = tag;
  cache->set[setIndex].line[cache->set[setIndex].fifo].isValid = true;
  cache->set[setIndex].fifo++;
  if (cache->set[setIndex].fifo >= cache->linesPerSet)
  {
    cache->set[setIndex].fifo = 0;
  }
}

void simulateCache(int cacheSize, int blockSize, char* replacePolicy, FILE* traceFile, char* associativity)
{
  // 12 bytes (48-bit) memory addresses
  // 1 LINE PER SET IN A DIRECT CACHE
  int linesPerSet;
  int numSets;
  int setBits;
  int dataBits;
  //int tagBits;
  // Determine the associativity of the cache //
  if (strcmp(associativity, "direct") == 0)
  {
    linesPerSet = 1; // property of directCache
    numSets = (cacheSize) / (linesPerSet*blockSize);
  }
  else if (strcmp(associativity, "assoc") == 0)
  {
    // only 1 set, no set bits required
    numSets = 1; // property of fully associative cache
    linesPerSet = (cacheSize) / (numSets*blockSize);
  }
  else
  {
    char* token = strtok(associativity, ":");
    token = strtok(NULL, ":");
    linesPerSet = atoi(token);
    //printf("assoc:%d\n", linesPerSet);
    numSets = (cacheSize) / (linesPerSet*blockSize);
  }
  setBits = log10(numSets) / log10(2);
  dataBits = log10(blockSize) / log10(2);
  // tagBits = 48 - setBits - dataBits;
  /* Initialize Cache */
  Cache cache = initializeCache(numSets, linesPerSet);
  //printf("%d %d %d\n", cache.sets[0].numValidLines = 30, cache.sets[0].lines[0].tag = 60, cache.sets[0].lines[0].data = 90);
  size_t programCount = 0;
  char action = '\0';
  size_t address = 0;
  while (fscanf(traceFile, "%lx: %c %lx", &programCount, &action, &address))
  {
    //printf("0x%lx\t: %c\t 0x%lx\t", programCount, action, cacheData);
    // Get the set # that the data will be stored in //
    int setIndex = (int)((address>>dataBits) % (int)(pow(2,(double)setBits)));
    // Get the tag of the data //
    size_t tag = address>>(dataBits+setBits);
    //printf("tag of %lx : \t", cacheData);
    //printBits(tag, 4*strlen(hexString));
    // Search for tag in set setIndex //
    bool hit = false;
    for (int i = 0; i < linesPerSet; i++)
    {
      if (cache.set[setIndex].line[i].isValid && cache.set[setIndex].line[i].tag == tag)
      {
          cacheHits++;
          hit = true;
          if (strcmp(replacePolicy, "lru") == 0)
          {
            updateLRU(&cache, hit, setIndex, tag, i);
          }
          break;
      }
    }
    if (action == 'R')
    {
      if (!hit)
      {
        cacheMiss++;
        if (strcmp(replacePolicy, "lru") == 0)
        {
          updateLRU(&cache, hit, setIndex, tag, -1);
        }
        else // strcmp(replacePolicy, "fifo") == 0
        {
          updateFIFO(&cache, setIndex, tag);
        }
        // read directly from memory to cache
        memReads++;
      }
    }
    else // action == 'W'
    {
      if (hit)
      {
        memWrites++;
      }
      else // (!hit)
      {
        cacheMiss++;
        // read directly from memory to cache
        // need to decide which line to evict
        if (strcmp(replacePolicy, "lru") == 0)
        {
          updateLRU(&cache, hit, setIndex, tag, -1);
        }
        else // strcmp(replacePolicy, "fifo") == 0
        {
          updateFIFO(&cache, setIndex, tag);
        }
        memReads++;
        // update line in cache
        memWrites++;
      }
    }
  }
  freeCache(cache);
}
