typedef struct {
  uint16_t limit;
  uint16_t base_low;
  uint16_t base_high;
} __attribute__((__packed__)) dtr;

dtr get_dtr(uint8_t selector)
{
  dtr dtrr;
  dtrr.limit = dtrr.base_low = dtrr.base_high = 0;

  switch (selector)
    {
    case 0:
      asm("sidt %0 \n\t" : "=m"(dtrr));
      break;

    case 1:
      asm("sgdt %0 \n\t" : "=m"(dtrr));
      break;
    }

  return dtrr;
}
