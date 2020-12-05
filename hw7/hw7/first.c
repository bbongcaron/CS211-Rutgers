#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Gate
{
  /* a Gate strcut to build the circuit with */
  char operation[5];
  char arg1[100];
  char arg2[100];
  char outputVar[100];
  struct Gate* next;
} Gate;

Gate* buildCircuit(FILE* circuit_file);
void freeCircuit(Gate* circuit);
void freeMatrix(char** matrix, int numElements);

int main(int argc, char* argv[argc+1])
{
  /* Open circuit file */
  FILE* circuit_file = fopen(argv[1], "r");
  /* Initialize/declare necessary variables */
  char** inVars; char** outVars;
  int numInputs = 0; int numOutputs = 0;
  Gate* circuit = NULL;
  /* scan INPUTVARS */
  fscanf(circuit_file, "%*s %d", &numInputs);
  inVars = malloc(sizeof(char*)*numInputs);
  printf("INPUTVAR %d", numInputs);
  for (int i = 0; i < numInputs; i++) {
    inVars[i] = malloc(sizeof(char)*100);
    fscanf(circuit_file, " %s", inVars[i]);
    printf(" %s", inVars[i]);
  }
  printf("\n");
  /* scan OUTPUTVARS */
  fscanf(circuit_file, "%*s %d", &numOutputs);
  outVars = malloc(sizeof(char*)*numOutputs);
  printf("OUTPUTVAR %d", numOutputs);
  for (int i = 0; i < numOutputs; i++) {
    outVars[i] = malloc(sizeof(char)*100);
    fscanf(circuit_file, " %s", outVars[i]);
    printf(" %s", outVars[i]);
  }
  printf("\n");
  /* scan circuit instructions */
  circuit = buildCircuit(circuit_file);
  /* Free all malloc'ed stuff */
  freeMatrix(inVars, numInputs);
  freeMatrix(outVars, numOutputs);
  freeCircuit(circuit);
  fclose(circuit_file);
  return EXIT_SUCCESS;
}

void freeMatrix(char** matrix, int numElements)
{
  /* Free matrix of char strings */
  for (int i = 0; i < numElements; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

void freeCircuit(Gate* circuit)
{
  /* Free circuit linked list */
  Gate* ptr = circuit;
  Gate* prev = NULL;
  while (ptr)
  {
    prev = ptr;
    ptr = ptr->next;
    free(prev);
  }
}

Gate* createGate(FILE* circuit_file, char* operation)
{
  Gate* newGate = malloc(sizeof(Gate));
  strcpy(newGate->operation, operation);
  /* Scan in arguments and output variables to fields of newGate */
  fscanf(circuit_file, "%s", newGate->arg1);
  fscanf(circuit_file, "%s", newGate->arg2);
  fscanf(circuit_file, "%s", newGate->outputVar);
  newGate->next = NULL;
  /* Debug | Output newGate fields */
  printf("%s ", operation);
  printf("%s ", newGate->arg1);
  printf("%s ", newGate->arg2);
  printf("%s\n", newGate->outputVar);
  return newGate;
}

Gate* buildCircuit(FILE* circuit_file)
{
  Gate* circuit = NULL;
  Gate* newGate = NULL;
  Gate* lastGate = circuit;
  char operation[10] = "\0";
  while (fscanf(circuit_file, "%s ", operation) != EOF)
  {
    // Malloc a newGate corresponding to operation for circuit
    newGate = createGate(circuit_file, operation);

    if (!circuit && !lastGate)
    {
      // Check: Returned circuit is empty
      // Action 1: Initialize circuit when first Gate is created
      circuit = newGate;
      // Action 2: When first Gate is created, set the lastGate to be that Gate
      lastGate = circuit;
    }
    else // The circuit already has at least 1 Gate
    {
      // Append newGate to the end of circuit (lastGate)
      lastGate->next = newGate;
      // Update the circuit's lastGate pointer
      lastGate = lastGate->next;
    }
  }
  return circuit;
}
