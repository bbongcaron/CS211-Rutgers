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
  int* lru;
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
  if (strcmp(replacePolicy, "lru") != 0 && strcmp(replacePolicy, "fifo") != 0)
  {
    return false;
  }
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
  return true;
}

void freeCache(Cache cache)
{
  for (int i = 0; i < cache.numSets; i++)
  {
    free(cache.set[i].lru);
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
    cache.set[i].lru = malloc(sizeof(int)*linesPerSet);
    cache.set[i].fifo = 0;
    cache.set[i].numValidLines = 0;
    cache.set[i].line = malloc(sizeof(Line)*linesPerSet);
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
    deleteElement(cache->set[setIndex].lru, cache->set[setIndex].numValidLines, i);
    cache->set[setIndex].lru[cache->set[setIndex].numValidLines - 1] = i;
    cache->set[setIndex].line[i].isValid = true;
    cache->set[setIndex].line[i].tag = tag;
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
      cache->set[setIndex].lru[cache->set[setIndex].numValidLines] = cache->set[setIndex].numValidLines;
      // now have an additional vaild line
      cache->set[setIndex].numValidLines++;
    }
    else // cache.set[setIndex].numValidLines >= linesPerSet
    {
      // get the index of the line to be replaced
      int replaceLine = cache->set[setIndex].lru[0];
      // shift all elements of the lfu array to the left by 1
      shiftLeft(cache->set[setIndex].lru, cache->linesPerSet);
      // the replaceLine is now the most recently used
      cache->set[setIndex].lru[cache->linesPerSet - 1] = replaceLine;
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
  int linesPerSet;
  int numSets;
  int setBits;
  int dataBits;
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
    numSets = (cacheSize) / (linesPerSet*blockSize);
  }
  setBits = log10(numSets) / log10(2);
  dataBits = log10(blockSize) / log10(2);
  /* Initialize Cache */
  Cache cache = initializeCache(numSets, linesPerSet);
  size_t programCount = 0;
  char action = '\0';
  size_t address = 0; // 12 bytes (48-bit) memory addresses
  while (fscanf(traceFile, "%lx: %c %lx", &programCount, &action, &address))
  {
    // Get the set # that the data will be stored in //
    int setIndex = (int)((address>>dataBits) % (int)(pow(2,(double)setBits)));
    // Get the tag of the data //
    size_t tag = address>>(dataBits+setBits);
    // Search for tag in set setIndex //
    bool hit = false;
    for (int i = 0; i < linesPerSet; i++)
    {
      if (cache.set[setIndex].line[i].isValid && cache.set[setIndex].line[i].tag == tag)
      {
          cacheHits++;
          hit = true;
          if (strcmp(replacePolicy, "lru") == 0)
            updateLRU(&cache, hit, setIndex, tag, i);
          break;
      }
    }
    if (action == 'R')
    {
      if (!hit)
      {
        cacheMiss++;
        if (strcmp(replacePolicy, "lru") == 0)
          updateLRU(&cache, hit, setIndex, tag, -1);
        else
          updateFIFO(&cache, setIndex, tag);
        memReads++; // missed, therefore read directly from memory to cache
      }
    }
    else // action == 'W'
    {
      if (hit) memWrites++; // old data already in cache, just overwrite memory
      else // (!hit)
      {
        cacheMiss++; // need to read directly old memory to cache
        if (strcmp(replacePolicy, "lru") == 0)
          updateLRU(&cache, hit, setIndex, tag, -1);
        else // strcmp(replacePolicy, "fifo") == 0
          updateFIFO(&cache, setIndex, tag);
        memReads++; // update line in cache with previous memory data
        memWrites++; // overwrite memory
      }
    }
  }
  freeCache(cache);
}
