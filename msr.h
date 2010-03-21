#include <linux/module.h>
#include <linux/kernel.h>

void (*old_handl_p)(void) = 0;
void (*new_handl_p)(void) = 0;

void hook(void)
{
  // Pointer to a pointer to a function
  asm("jmp *%0" : : "m"(old_handl_p));
  return;
}

int init_module(void)
{
  new_handl_p = &hook;

  asm("rdmsr\n\t"
      : "=a"(old_handl_p)
      : "c"(0x176)
      : "%edx");
  
  /*  asm("wrmsr\n\t"
      : /* No output 
      : "c"(0x176), "d"(0x0), "a"(new_handl_p));*/
      
  printk(KERN_INFO "%p\n", old_handl_p);
  return 0;
}
