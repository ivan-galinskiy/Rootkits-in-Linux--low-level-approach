typedef struct
{
  uint16_t offset_low;
  uint32_t not_used; /* We are not going to use that */
  uint16_t offset_high;
} __attribute__((__packed__)) idt_entry;
/* __packed__ is needed to avoid structure alignment, otherwise it will
   not be suitable for use */

idt_entry* get_idt_entry(dtr idtr, uint index)
{
  idt_entry* entry = (idt_entry*) ((idtr.base_high << 16) + idtr.base_low);
  entry += index;
  return entry;
}

inline void modify_idt_entry_addr(idt_entry* entry, new_addr)
{
  __asm__("cli\n\t");
  entry->offset_high = (uint32_t)new_addr >> 16;
  entry->offset_low = (uint32_t)new_addr & 0x0000ffff;
  __asm__("sti\n\t");
}
