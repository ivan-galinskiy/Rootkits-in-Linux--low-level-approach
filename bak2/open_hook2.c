#include <linux/module.h>
#include <linux/kernel.h>
#include "sidt.h"
#include "idt.h"
#include "search.h"
#include "syscall.h"

void (*do_sys_open)(void) = 0;

void hook(void)
{
  asm("jmpl *%0"
      : /* No output */
      : "m"(do_sys_open));
  return;
}

int init_module()
{
  void* sys_call_table = 0;
  void* sys_open_p = 0;

  void* do_sys_open_rel_p = 0;
  int32_t do_sys_open_rel = 0;

  sys_call_table = find_sys_call_table();
  sys_open_p = read_sys_call_entry(sys_call_table, 5);

  do_sys_open_rel_p = search((uint8_t*)sys_open_p, (uint32_t)0x89f153e8, 64);
  do_sys_open_rel = *((int32_t*)do_sys_open_rel_p);

  do_sys_open = (void*) ((uint32_t)do_sys_open_rel_p + 4 + do_sys_open_rel);

  int32_t new_offset = (int32_t)
    ((uint32_t)hook - ((uint32_t)do_sys_open_rel_p + 4));
  asm("mov %%eax, (%%ebx)\n\t"
      : "=b"(do_sys_open_rel_p)
      : "a"(new_offset));

  return 0;
}

void cleanup_module(){}
