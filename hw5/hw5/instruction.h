#ifndef INSTRUCTION_H
#define INSTRUCTION_H

  /*
   *  @Instruction  struct representing a line of assembly code
   */
  typedef struct Instruction
  {
    char* action;
    char* arg1;
    char* arg2;
    char* arg3;
  } Instruction;

  /*
   *  @createInstruction  creates an Instruction struct
   */
  void createInstruction(Instruction**, char*, char*, char*, char*);
  /*
   *  @freeInstruction    frees an Instruction struct
   */
  void freeInstruction(Instruction**);

#endif
