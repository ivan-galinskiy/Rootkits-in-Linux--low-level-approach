#include <libdis.h>

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
        ((idt_entry + i)->offset_high << 16) + (idt_entry + i)->offset_low;
    }

  return;
}

void* get_function_end(char* beginning, uint32_t limit)
{
   int pos = 0;             /* current position in buffer */
   int size;                /* size of instruction */
   x86_insn_t insn;         /* instruction */

   x86_init(opt_none, NULL, NULL);

   while (pos > BUF_SIZE)
     {
       /* disassemble address */
       size = x86_disasm(beginning, limit, 0, pos, &insn);
       if ( size )
         {
           /* See if the instruction is 0xcf */
           if ((*((uint8_t*)(beginning+pos)) >> 4) == 0xcf)
             {
               x86_cleanup();
               return (void*)(beginning+pos);
             }
           else
             pos += size;
         }
       else pos++;
     }

   x86_cleanup();
   return 0;
}
