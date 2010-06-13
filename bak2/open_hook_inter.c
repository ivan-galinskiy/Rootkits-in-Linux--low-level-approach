long hook(int dfd, const char *filename, int flags, int mode)
{
  asm("pusha\n\t");
  char* p = filename;
  while (*p != '\0') p++; // Find the end of the string
  
  if (*(p-1) != 't' && *(p-2) != 's') // Check its ending
    {
      asm("popa\n\t");
      asm("jmpl *%0\n\t"
  	  : /* No output */
  	  : "m"(do_sys_open));
    }
  asm("popa\n\t");
  return -1; // Simulation of an error
}
