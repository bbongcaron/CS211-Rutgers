#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "instruction.h"

int main(int argc, char* argv[])
{
  /* Array of instructions representing a .asm file */
  Instruction* program[101];
  /* Pointer to the current line in the assembly program */
  int currentLine = 1;

  Instruction* i = NULL;
  createInstruction(&i, "print", "ax", "\0", "\0");
  printf("action = %s\n", i->action);
  printf("arg1 = %s\n", i->arg1);
  printf("arg2 = %s\n", i->arg2);
  printf("arg3 = %s\n", i->arg3);
  freeInstruction(&i);
}
