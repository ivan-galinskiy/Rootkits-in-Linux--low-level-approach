void (*old_handl_p)(void) = 0;
void (*new_handl_p)(void) = 0;

void hook(void)
{
  /* Pointer to the original handler */
  asm("jmp *%0" : : "m"(old_handl_p));
  return;
}

int init_module(void)
{
  new_handl_p = &hook;

  asm("rdmsr\n\t"
      : "=a"(old_handl_p) /* EAX now has a pointer to the hook */
      : "c"(0x176) /* Number of MSR register */
      : "%edx"); /* RDMSR also changes the EDX register */
  
  asm("wrmsr\n\t"
      : /* No output */
      : "c"(0x176), "d"(0x0), "a"(new_handl_p));
  
  return 0;
}
