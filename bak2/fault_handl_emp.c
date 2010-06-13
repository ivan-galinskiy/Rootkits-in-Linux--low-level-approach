#include <linux/module.h>
#include <linux/kernel.h>
#include "sidt.h"
#include "idt.h"

void* old_page_fault = 0;
idt_entry* pf_ent_p = 0;

void new_page_fault(void)
{
  __asm__("jmpl *%0\n\t"
          :
          : "m"(old_page_fault));
}

int init_module()
{
  pf_ent_p = get_idt_entry(get_idtr(), 0x0e);
  old_page_fault = (void*)((pf_ent_p->offset_high << 16) +
                           pf_ent_p->offset_low);

  // Setting the new handler
  __asm__("cli\n\t");
  pf_ent_p->offset_high = (uint32_t)&new_page_fault >> 16;
  pf_ent_p->offset_low = (uint32_t)&new_page_fault & 0x0000ffff;
  __asm__("sti\n\t");

  return 0;
}

void cleanup_module()
{
  __asm__("cli\n\t");
  pf_ent_p->offset_high = (uint32_t)old_page_fault >> 16;
  pf_ent_p->offset_low = (uint32_t)old_page_fault & 0x0000ffff;
  __asm__("sti\n\t");
}
