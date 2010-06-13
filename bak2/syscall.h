void* find_sys_call_table(void)
{
  void* ia32_sysenter_target_p = 0;
  void* sys_call_table_p = 0;
  void* sys_call_table_pp = 0;

  asm("rdmsr\n\t"
      : "=a"(ia32_sysenter_target_p)
      : "c"(0x176)
      : "%edx");

  /* This is technically a pointer to a pointer */
  sys_call_table_pp =
    search((uint8_t*)ia32_sysenter_target_p, 0x00ff1485, 512);

  /* Convert to uint32_t, read (32 bits) and convert obtained
     value to void* */
  sys_call_table_p =
    (void*) (*((uint32_t*)sys_call_table_pp));

  return sys_call_table_p;
}

void* read_sys_call_entry(void* sys_call_table, int index)
{
  void* entry_p = sys_call_table + 4 * index;
  uint32_t entry = *((uint32_t*)entry_p);
  return (void*)entry;
}
