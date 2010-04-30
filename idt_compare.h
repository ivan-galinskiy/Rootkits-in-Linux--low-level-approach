#include "hde28c/hde32.c"

typedef struct
{
  uint16_t offset_low;
  uint32_t not_used; /* We are not going to use that */
  uint16_t offset_high;
} __attribute__((__packed__)) idt_entry;

void get_idt_addresses(int32_t* buffer, idt_entry* idt)
{
  for(int i = 0; i <= 255; i++)
    {
      *(buffer + i) =
        ((idt + i)->offset_high << 16) + (idt + i)->offset_low;
    }

  return;
}

void* get_function_end(char* beginning)
{
  hde32s instr; // Instruction structure
  unsigned int length = 0;
  
  while (instr.opcode != 0xC3 || instr.opcode != 0xCB || // ret
         instr.opcode != 0xCF) // iret
    {
      beginning += length;
      length = hde32_disasm(beginning, &instr);
    }
  
  return (void*)beginning;
}
