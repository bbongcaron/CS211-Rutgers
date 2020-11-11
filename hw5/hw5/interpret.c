#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"

void resetTemps(char* action, char* arg1, char* arg2, char* arg3);

void freeProgram(Instruction* program[], int endOfProgram);

int main(int argc, char* argv[])
{
  /* Array of instructions representing a .asm file */
  Instruction* program[101];
  /* Pointer to the current line in the assembly program */
  //int currentLine = 1;
  /* Pointer to the end of the assembly program */
  int endOfProgram = 1;
  FILE* asm = fopen(argv[1], "r");

  /* Declaration of temporary placeholders of assembly strings */
  char line[100] = "\0";
  char action[6] = "\0";
  char arg1[6] = "\0";
  char arg2[6] = "\0";
  char arg3[6] = "\0";

  /* Go through each line of the .asm file */
  while(fgets(line, 100, asm) != NULL)
  {
    char* token = strtok(line, " \n");
    /* If statement checks for empty lines */
    if (!token)
    {
      continue;
    }
    strcpy(action, token);
    token = strtok(NULL, " \n");
    /* Next argument number in line to be filled up */
    int currentArg = 1;
    while (token && strcmp(token, "\n") != 0)
    {
      /* Switch statement keeps track of how many args have been read in */
      switch (currentArg)
      {
        case 1 :
          strcpy(arg1, token);
          break;
        case 2 :
          strcpy(arg2, token);
          break;
        case 3 :
          strcpy(arg3, token);
          break;
      }
      currentArg++;
      token = strtok(NULL, " \n");
    }
    /* Create an Instruction struct for line endOfProgram */
    Instruction* i = NULL;
    createInstruction(&i, action, arg1, arg2, arg3);
    /* Add Instruction i to program[endOfProgram] */
    program[endOfProgram] = i;
    endOfProgram++;
    /* Reset temporary variables */
    resetTemps(action, arg1, arg2, arg3);
  }

  freeProgram(program, endOfProgram);

}

void resetTemps(char* action, char* arg1, char* arg2, char* arg3)
{
  strcpy(action, "\0");
  strcpy(arg1, "\0");
  strcpy(arg2, "\0");
  strcpy(arg3, "\0");
  return;
}

void freeProgram(Instruction* program[], int endOfProgram)
{
  for (int x = 1; x < endOfProgram; x++)
  {
    /* Comment out code printing as necessary */
    printf("%d | %s %s %s %s\n", x, program[x]->action, program[x]->arg1, program[x]->arg2, program[x]->arg3);
    freeInstruction(&program[x]);
  }
  return;
}
