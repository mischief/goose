#ifndef UCONTEXT_H
#define UCONTEXT_H

#include <u.h>
#include <signal.h>

typedef struct mcontext_t {
  /* segments */
  ulong gs;
  ulong fs;
  ulong es;
  ulong ds;

  /* PUSHA regs */
  ulong edi;
  ulong esi;
  ulong ebp;
  ulong esp; /* a lie? */
  ulong ebx;
  ulong edx;
  ulong ecx;
  ulong eax;

  /* trap #, 0-31 */
  ulong trapno;

  /* processor errno 0 if none */
  ulong err;

  /* process state frame */
  ulong *eip;
  ulong cs;
  ulong eflags;
//  ulong esp;
  ulong ss;
} mcontext_t;

typedef struct ucontext_t {
  struct ucontext_t *uc_link;
  //sigset_t uc_sigmask;
  stack_t uc_stack;
  mcontext_t uc_mcontext;
} ucontext_t;

extern int  swapcontext(ucontext_t *oucp, const ucontext_t *ucp);
extern void makecontext(ucontext_t *ucp, void (*func)(void), int argc, ...);
extern int  getcontext(ucontext_t *);
extern int  setcontext(const ucontext_t *);

#endif
