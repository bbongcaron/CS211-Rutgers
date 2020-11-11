#include "instruction.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void createInstruction(Instruction** instruction, char* act, char* a1, char* a2, char* a3)
{
  Instruction* i = malloc(sizeof(Instruction));
  /* longest action is "print" --> max string length is 6 (including /0) */
  i->action = malloc(sizeof(char) * 6);
  /* largest 16-bit int is 65535 --> 5 digits --> max string length is 6 */
  i->arg1 = malloc(sizeof(char) * 6);
  i->arg2 = malloc(sizeof(char) * 6);
  i->arg3 = malloc(sizeof(char) * 6);
  strcpy(i->action, act);
  strcpy(i->arg1, a1);
  strcpy(i->arg2, a2);
  strcpy(i->arg3, a3);
  *instruction = i;
  return;
}

void freeInstruction(Instruction** i)
{
  Instruction* ptr = *i;
  free(ptr->action);
  free(ptr->arg1);
  free(ptr->arg2);
  free(ptr->arg3);
  free(ptr);
}
