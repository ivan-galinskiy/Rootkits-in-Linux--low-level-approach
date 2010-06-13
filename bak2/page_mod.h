void set_rw_flag(void* p, bool value)
{
  uint32_t cr3;

  uint16_t dir_index;
  uint32_t* dir_entry;
  
  uint32_t ptable_p;
  uint32_t ptable_index;
  uint32_t* ptable_entry;

  asm("movl %%cr3, %%eax\n\t"
      : "=a"(cr3));

  dir_index = ((uint32_t)p & 0xffc00000) >> 22; /* First 10 bits */
  dir_entry = (uint32_t*)(cr3 + dir_index);

  ptable_p = dir_entry & 0xfffff000; /* Bits 31-12 of the entry */
  ptable_index = ((uint32_t)p & 0x3ff000) >> 12; /* Second 10 bits */
  ptable_entry = (uint32_t*)(ptable_p + ptable_index);

  *ptable_entry |= 2; /* Enable second bit (Write mode) */

  return 0;
}
