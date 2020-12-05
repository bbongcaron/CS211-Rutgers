#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Gate
{
  char operation[5];
  char arg1[100];
  char arg2[100];
  char outputVar[100];
  struct Gate* next;
} Gate;

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
  char** inVars; char** outVars;
  int numInputs = 0; int numOutputs = 0;
  Gate* circuit = NULL;

  /* scan INPUTVARS */
  fscanf(circuit_file, "%*s %d", &numInputs);
  inVars = malloc(sizeof(char*)*numInputs);
  //printf("INPUTVAR");
  for (int i = 0; i < numInputs; i++) {
    inVars[i] = malloc(sizeof(char)*100);
    fscanf(circuit_file, " %s", inVars[i]);
    //printf(" %s", inVars[i]);
  }
  //printf("\n");
  /* scan OUTPUTVARS */
  fscanf(circuit_file, "%*s %d", &numOutputs);
  outVars = malloc(sizeof(char*)*numOutputs);
  //printf("OUTPUTVAR");
  for (int i = 0; i < numOutputs; i++) {
    outVars[i] = malloc(sizeof(char)*100);
    fscanf(circuit_file, " %s", outVars[i]);
    //printf(" %s", outVars[i]);
  }
  //printf("\n");
  freeMatrix(inVars, numInputs);
  freeMatrix(outVars, numOutputs);
  fclose(circuit_file);
  return EXIT_SUCCESS;
}
