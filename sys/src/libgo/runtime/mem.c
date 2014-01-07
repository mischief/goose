/* Defining _XOPEN_SOURCE hides the declaration of madvise() on Solaris <
   11 and the MADV_DONTNEED definition on IRIX 6.5.  */
#undef _XOPEN_SOURCE

//#include <errno.h>
//#include <unistd.h>

#include "runtime.h"
#include "arch.h"
#include "malloc.h"

static Lock memlock;

void*
runtime_SysAlloc(uintptr n)
{
  void *p;

  p = malloc(n);

	if (p == nil) {
			runtime_prints("runtime: malloc: out of memory\n");
			exit(2);
  }	
	return p;
}

void
runtime_SysUnused(void *v __attribute__ ((unused)), uintptr n __attribute__ ((unused)))
{
}

void
runtime_SysFree(void *v, uintptr n)
{
	mstats.sys -= n;
  free(v);
}

void*
runtime_SysReserve(void *v, uintptr n)
{
  return runtime_SysAlloc(n);
}

void
runtime_SysMap(void *v, uintptr n)
{
}
