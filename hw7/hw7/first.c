#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void freeMatrix(char** matrix, int numElements)
{
  for (int i = 0; i < numElements; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

int main(int argc, char* argv[argc+1])
{
  FILE* circuit_file = fopen(argv[1], "r");
  char action[10] = "\0";
  char** inVars; char** outVars;
  int numInputs = 0; int numOutputs = 0;
  while (fscanf(circuit_file, "%s", action) != EOF)
  {
    if (strcmp(action, "INPUTVAR") == 0)
    {
      fscanf(circuit_file, " %d", &numInputs);
      inVars = malloc(sizeof(char*)*numInputs);
      for (int i = 0; i < numInputs; i++) {
        inVars[i] = malloc(sizeof(char)*100);
        fscanf(circuit_file, " %s", inVars[i]);
      }
    }
    else if (strcmp(action, "OUTPUTVAR") == 0)
    {
      fscanf(circuit_file, " %d", &numOutputs);
      outVars = malloc(sizeof(char*)*numOutputs);
      for (int i = 0; i < numOutputs; i++) {
        outVars[i] = malloc(sizeof(char)*100);
        fscanf(circuit_file, " %s", outVars[i]);
      }
    }
  }
  freeMatrix(inVars, numInputs);
  freeMatrix(outVars, numOutputs);
  fclose(circuit_file);
  return EXIT_SUCCESS;
}
