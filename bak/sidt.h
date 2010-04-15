typedef struct {
  uint16_t limit;
  uint16_t base_low;
  uint16_t base_high;
} dtr;

dtr get_idtr(void)
{
  dtr idtr;
  idtr.limit = 0;
  idtr.base_low = idtr.base_high = 0;

  asm("sidt %0 \n\t"
      : "=m"(idtr));

  return idtr;
}
