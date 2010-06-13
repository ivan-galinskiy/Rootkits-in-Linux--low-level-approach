#include "hde32.c"
#include <stdio.h>
#include <stdint.h>

int foo()
{
  return 25;
}


int main(int argc, char *argv[])
{
  hde32s temp;
  uint8_t* func = (uint8_t*)foo;
  unsigned int length;
  int a = foo();
  printf("%d\n", a);
  printf("%X\n", func);

  while (temp.opcode != 0xC3)
    {
      length = hde32_disasm(func, &temp);
      func += length;
      printf("0x%X\n", temp.opcode);
    }

  printf("\n%X\n", func);
  return 0;
}

