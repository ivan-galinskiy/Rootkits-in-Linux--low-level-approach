void* search(uint8_t* base, uint32_t pattern, uint limit)
{
  /* Reversing the byte order in the pattern, because int is
   stored reversed, but we need to find straight patterns*/
  uint32_t pattern_reversed = (pattern << 24) + (pattern >> 24) +
    ((pattern & 0x0000ff00) << 8) +
    ((pattern & 0x00ff0000) >> 8);

  int c;
  for (c=0; c < limit; c++)
    {
      /* We add c bytes to the pointer, convert it to uint_32
         and then compare (if found, we add 4 so it points to
         the next byte) */
      uint8_t* base_cur = base + c;
      if (*((uint32_t*)(base_cur)) == pattern_reversed)
        return (void*)(base_cur + 4);
    }

  /* Nothing found */
  return (void*)0;
}
