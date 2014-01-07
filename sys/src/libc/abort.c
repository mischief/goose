#include <u.h>
#include <libc.h>

void
abort(void)
{
  exit(255);
}

