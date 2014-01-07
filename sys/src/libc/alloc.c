#include <u.h>

static unsigned mem = (unsigned) 0x100000;
extern unsigned end[];

void *
malloc(size_t size)
{
  static char *p;
  void *q;

  if(p == nil) {
    p = (char*)((unsigned)end & 0xFFFFF000) + 0x1000;
    //p += 7 & -(uintptr)p;
  }

  size += 7 & -size;

  q = p;
  p += size;
  return q;
}

void
free(void *v)
{
}

