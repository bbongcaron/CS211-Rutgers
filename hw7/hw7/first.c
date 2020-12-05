#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
typedef struct Gate
{
  /* a Gate strcut to build the circuit with */
  char operation[5];
  char arg1[100];
  char arg2[100];
  char outputVar[100];
  struct Gate* next;
} Gate;

void freeCircuit(Gate* circuit);
void freeCharMatrix(char** matrix, int numRows);
void freeIntMatrix(int** matrix, int numRows);
int** buildTruthTable(int numInputs, int numOutputs);
void printTruthTable(int** truthTable, int numRows, int numCols);
Gate* buildCircuit(FILE* circuit_file);
void runCircuit(Gate* circuit, int** truthTable, char** inVars, char** outVars,
                int numInputs, int numOutputs);

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
  //printf("INPUTVAR %d", numInputs);
  for (int i = 0; i < numInputs; i++) {
    inVars[i] = malloc(sizeof(char)*100);
    fscanf(circuit_file, " %s", inVars[i]);
    //printf(" %s", inVars[i]);
  }
  //printf("\n");
  /* scan OUTPUTVARS */
  fscanf(circuit_file, "%*s %d", &numOutputs);
  outVars = malloc(sizeof(char*)*numOutputs);
  //printf("OUTPUTVAR %d", numOutputs);
  for (int i = 0; i < numOutputs; i++) {
    outVars[i] = malloc(sizeof(char)*100);
    fscanf(circuit_file, " %s", outVars[i]);
    //printf(" %s", outVars[i]);
  }
  //printf("\n");
  /* scan circuit instructions */
  circuit = buildCircuit(circuit_file);
  /* Initialize output truth table */
  int** truthTable = buildTruthTable(numInputs, numOutputs);

  // need code here to calculate outputs
  runCircuit(circuit, truthTable, inVars, outVars, numInputs, numOutputs);
  /* Print out resulting truth table */
  printTruthTable(truthTable, (int)(pow(2, numInputs)), numInputs + numOutputs);
  /* Free all malloc'ed stuff */
  freeCharMatrix(inVars, numInputs);
  freeCharMatrix(outVars, numOutputs);
  freeIntMatrix(truthTable, (int)(pow(2, numInputs)));
  freeCircuit(circuit);
  fclose(circuit_file);
  return EXIT_SUCCESS;
}

void printTruthTable(int** truthTable, int numRows, int numCols)
{
  for(int i = 0; i < numRows; i++)
  {
    printf("%d", truthTable[i][0]);
    for (int j = 1; j < numCols; j++)
    {
      printf(" %d", truthTable[i][j]);
    }
    printf("\n");
  }
}

void freeCharMatrix(char** matrix, int numRows)
{
  /* Free double array */
  for (int i = 0; i < numRows; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

void freeIntMatrix(int** matrix, int numRows)
{
  /* Free double array */
  for (int i = 0; i < numRows; i++)
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

int** buildTruthTable(int numInputs, int numOutputs)
{
  /* Initialize empty truth table */
  int numRows = (int)(pow(2, numInputs));
  int numCols = numInputs + numOutputs;
  int** truthTable = malloc(sizeof(int*)*numRows);
  for (int i = 0; i < numRows; i++)
  {
    truthTable[i] = malloc(sizeof(int)*(numCols));
  }
  /* Fill in input columns */
  int colsFilled = 0;
  for (int c = numCols - 1 - numOutputs; c >= 0; c--)
  {
    /* Algorithm to fill in input columns */
    int currentRow = 1;
    bool one = false;
    for(int r = 0; r < numRows; r++)
    {
      if (one) truthTable[r][c] = 1;
      else truthTable[r][c] = 0;
      /* currentRow MOD 2^colsFilled gives correct alternating pattern */
      if (currentRow % (int)pow(2, colsFilled) == 0) one = !one;
      currentRow++;
    }
    colsFilled++;
  }
  return truthTable;
}

Gate* createGate(FILE* circuit_file, char* operation)
{
  Gate* newGate = malloc(sizeof(Gate));
  strcpy(newGate->operation, operation);
  /* Scan in arguments and output variables to fields of newGate */
  fscanf(circuit_file, "%s", newGate->arg1);
  if (strcmp(operation, "NOT") != 0) fscanf(circuit_file, "%s", newGate->arg2);
  fscanf(circuit_file, "%s", newGate->outputVar);
  newGate->next = NULL;
  /* Debug | Output newGate fields
  printf("%s ", operation);
  printf("%s ", newGate->arg1);
  if (strcmp(operation, "NOT") != 0) printf("%s ", newGate->arg2);
  printf("%s\n", newGate->outputVar);
  */
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

typedef struct Variable{
  char name[100];
  int value;
} Variable;

void runCircuit(Gate* circuit, int** truthTable, char** inVars, char** outVars,
                int numInputs, int numOutputs)
{
  int numRows = (int)(pow(2, numInputs));
  for (int i = 0; i < numRows; i++)
  {
    /* Malloc 1D arrays of Variable structs: contains names & boolean values */
    Variable* inputs = malloc(sizeof(Variable)*numInputs);
    Variable* outputs = malloc(sizeof(Variable)*numOutputs);
    /* Assign truth values based on pre-made truth table input rows */
    for (int j = 0; j < numInputs; j++)
    {
      /* Assign input Variable names & values based on inVars & truthTable */
      strcpy(inputs[j].name, inVars[j]);
      inputs[j].value = truthTable[i][j];
    }
    for (int j = 0; j < numOutputs; j++)
    {
      /* Assign output Variable names based in outVars */
      strcpy(outputs[j].name, outVars[j]);
    }
    /* Initialize gate pointer */
    Gate* currentGate = circuit;
    while (currentGate)
    {
      int inputOneIndex = 0; int inputTwoIndex = 0;
      bool foundOne = false;
      bool foundTwo;
      if (strcmp(currentGate->operation, "NOT") != 0) foundTwo = false;
      else foundTwo = true;
      int outputIndex = 0; bool foundOut = false;
      /* Find indexes of Gate inputs in Variable arrays to pull boolean values */
      while (!foundOne || !foundTwo ||!foundOut)
      {
        if (!foundOne)
        {
          if (strcmp(inputs[inputOneIndex].name, currentGate->arg1) == 0)
            foundOne = true;
          else inputOneIndex++;
        }
        if (!foundTwo)
        {
          if (strcmp(inputs[inputTwoIndex].name, currentGate->arg2) == 0)
            foundTwo = true;
          else inputTwoIndex++;
        }
        if (!foundOut)
        {
          if (strcmp(outputs[outputIndex].name, currentGate->outputVar) == 0)
            foundOut = true;
          else outputIndex++;
        }
      }
      if (strcmp(currentGate->operation, "AND") == 0)
      {
        outputs[outputIndex].value = inputs[inputOneIndex].value
                                                && inputs[inputTwoIndex].value;
      }
      else if (strcmp(currentGate->operation, "OR") == 0)
      {
        outputs[outputIndex].value = inputs[inputOneIndex].value
                                                || inputs[inputTwoIndex].value;
      }
      else if (strcmp(currentGate->operation, "NAND") == 0)
      {
        outputs[outputIndex].value = !(inputs[inputOneIndex].value
                                                && inputs[inputTwoIndex].value);
      }
      else if (strcmp(currentGate->operation, "NOR") == 0)
      {
        outputs[outputIndex].value = !(inputs[inputOneIndex].value
                                                || inputs[inputTwoIndex].value);
      }
      else if (strcmp(currentGate->operation, "NOT") == 0)
      {
        outputs[outputIndex].value = !(inputs[inputOneIndex].value);
      }
      else if (strcmp(currentGate->operation, "XOR") == 0)
      {
        outputs[outputIndex].value = (inputs[inputOneIndex].value
                                    || inputs[inputTwoIndex].value)
                                  && !(inputs[inputOneIndex].value
                                    && inputs[inputTwoIndex].value);
      }
      /* Fill in solved outputs in the corresponding truthTable row */
      for (int j = 0; j < numOutputs; j++)
        truthTable[i][numInputs + j] = outputs[j].value;

      currentGate = currentGate->next;
    }
    free(inputs);
    free(outputs);
  }
}
