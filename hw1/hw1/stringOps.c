#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isVowel(char c)
{
  if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U'
   || c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
   {
     return 1;
   }
  return 0;
}
int main(int argc, char* argv[argc+1])
{
  /* count the number of vowels in every string entered */
  int numVowels = 0;
  for (int i = 1; i < argc; i++)
  {
    for (int j = 0; j < strlen(argv[i]); j++)
    {
      if (isVowel(argv[i][j]) == 1)
      {
        numVowels++;
      }
    }
  }
  /* allocate a character array with size equal to the number of vowels */
  char* vowels = malloc(sizeof(char) * numVowels);
  int counter = 0;

  /* grab the vowels and put them into the character array */
  for (int i = 1; i < argc; i++)
  {
    for (int j = 0; j < strlen(argv[i]); j++)
    {
      if (isVowel(argv[i][j]) == 1)
      {
        vowels[counter] = argv[i][j];
        counter++;
      }
    }
  }
  /* output the vowels */
  for (int i = 0; i < numVowels; i++)
  {
    printf("%c", vowels[i]);
  }
  printf("\n");
  /* free the vowels array */
  free(vowels);
}
