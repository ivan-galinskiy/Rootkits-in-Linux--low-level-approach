typedef struct
{
  uint16_t offset_low;
  uint16_t selector; /* Target segment selector */
  uint8_t  zero;
  uint8_t  type_attr;
  uint16_t offset_high;
} idt_entry;

idt_entry* get_idt_entry(dtr idtr, uint index)
{
  idt_entry* entry = (idt_entry*) ((idtr.base_high << 16) + idtr.base_low);
  entry += index;
  return entry;
}
