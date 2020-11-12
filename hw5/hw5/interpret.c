#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"
#include "io.h"
#include "arithmetic.h"
#include "jump.h"

void resetTemps(char* action, char* arg1, char* arg2, char* arg3);
int makeProgram(FILE* asm, Instruction* program[]);
void runProgram(Instruction* program[], int lastLine);
void printProgram(Instruction* program[], int lastLine);
void freeProgram(Instruction* program[], int lastLine);

int main(int argc, char* argv[])
{
  /* Array of instructions representing a .asm file */
  Instruction* program[101];

  /* Assembly file to be scanned */
  FILE* asm = fopen(argv[1], "r");

  /* Pointer to the end of the assembly program */
  int lastLine = makeProgram(asm, program);
  printProgram(program,lastLine);
  runProgram(program, lastLine);
  /* new line for formatting purposes */
  printf("\n");
  /* Free all malloc'ed portions of program */
  freeProgram(program,lastLine);
}

void resetTemps(char* action, char* arg1, char* arg2, char* arg3)
{
  strcpy(action, "\0");
  strcpy(arg1, "\0");
  strcpy(arg2, "\0");
  strcpy(arg3, "\0");
  return;
}

int makeProgram(FILE* asm, Instruction* program[])
{
  /* Declaration of temporary placeholders of assembly strings */
  char line[100] = "\0";
  char action[6] = "\0";
  char arg1[6] = "\0";
  char arg2[6] = "\0";
  char arg3[6] = "\0";
  /* Pointer to end of program */
  int lastLine = 1;
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
    program[lastLine] = i;
    /* Update endOfProgram */
    lastLine++;
    /* Reset temporary variables */
    resetTemps(action, arg1, arg2, arg3);
  }
  return lastLine;
}

void runProgram(Instruction* program[], int lastLine)
{
  for (int currentLine = 1; currentLine < lastLine; currentLine++)
  {
    if (strcmp(program[currentLine]->action, "read") == 0)
    {
      read(program[currentLine]->arg1);
    }
    else if (strcmp(program[currentLine]->action, "print") == 0)
    {
      print(program[currentLine]->arg1);
    }
    else if (strcmp(program[currentLine]->action, "move") == 0)
    {
      move(program[currentLine]->arg1, program[currentLine]->arg2);
    }
    else if (strcmp(program[currentLine]->action, "add") == 0)
    {
      add(program[currentLine]->arg1, program[currentLine]->arg2);
    }
    else if (strcmp(program[currentLine]->action, "sub") == 0)
    {
      sub(program[currentLine]->arg1, program[currentLine]->arg2);
    }
    else if (strcmp(program[currentLine]->action, "mul") == 0)
    {
      mul(program[currentLine]->arg1, program[currentLine]->arg2);
    }
    else if (strcmp(program[currentLine]->action, "div") == 0)
    {
      divide(program[currentLine]->arg1, program[currentLine]->arg2);
    }
    else if (strcmp(program[currentLine]->action, "jmp") == 0)
    {
      currentLine = atoi(program[currentLine]->arg1) - 1;
    }
    else if (strcmp(program[currentLine]->action, "je") == 0)
    {
      if (je(program[currentLine]->arg2, program[currentLine]->arg3))
      {
        currentLine = atoi(program[currentLine]->arg1) - 1;
      }
    }
    else if (strcmp(program[currentLine]->action, "jne") == 0)
    {
      if (jne(program[currentLine]->arg2, program[currentLine]->arg3))
      {
        currentLine = atoi(program[currentLine]->arg1) - 1;
      }
    }
    else if (strcmp(program[currentLine]->action, "jg") == 0)
    {
      if (jg(program[currentLine]->arg2, program[currentLine]->arg3))
      {
        currentLine = atoi(program[currentLine]->arg1) - 1;
      }
    }
  }
  return;
}

void printProgram(Instruction* program[], int lastLine)
{
  for (int x = 1; x < lastLine; x++)
  {
    printf("%d | %s %s %s %s\n", x, program[x]->action, program[x]->arg1, program[x]->arg2, program[x]->arg3);
  }
}

void freeProgram(Instruction* program[], int lastLine)
{
  for (int x = 1; x < lastLine; x++)
  {
    freeInstruction(&program[x]);
  }
  return;
}
