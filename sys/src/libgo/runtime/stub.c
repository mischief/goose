/* for anything not imported from libgo yet,
   but requires a stub to link. */

#include "runtime.h"

const byte *
runtime_getenv(const char *s)
{
  if(strcmp(s, "GOGCTRACE") == 0) {
    return "1";
  }
  return nil;
}

void goexit(int code) __asm__ (GOSYM_PREFIX "runtime.Exit");

void goexit(int code) {
  exit(code);
}

unsigned
getpagesize(void)
{
  return 0x1000;
}
