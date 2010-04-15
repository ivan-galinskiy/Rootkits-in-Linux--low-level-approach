#include <linux/module.h>
#include <linux/kernel.h>
#include "sidt.h"
#include "idt.h"
#include "search.h"
#include "syscall.h"

int init_module()
{
  void* sys_call_table = find_sys_call_table();
  void* sys_call_entry = read_sys_call_entry(sys_call_table, 5);
  printk(KERN_INFO "%X\n", (uint32_t)sys_call_entry);
  return 0;
}

void cleanup_module(){}
