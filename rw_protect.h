void rw_protection_set(bool enabled)
{
  int32_t cr0;
  asm("mov %%cr0, %0\n\t"
      : "=r"(cr0));

  if (enabled)
    cr0 |= (1 << 16);
  else
    cr0 &= ~(1 << 16);

  asm("mov %0, %%cr0\n\t"
      :
      : "r"(cr0));
  return;
}
