#include <u.h>
#include <libc.h>

void
gettimeofday(struct timeval *tv, void *v)
{
  tv->tv_sec = 0;
  tv->tv_usec = 0;
}
