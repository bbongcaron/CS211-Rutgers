#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
  FILE* in_file = fopen(argv[1], "r");
  fclose(in_file);
}
