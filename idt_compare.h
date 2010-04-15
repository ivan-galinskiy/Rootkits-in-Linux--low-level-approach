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

void* get_function_end(void* beginning)
{
  
