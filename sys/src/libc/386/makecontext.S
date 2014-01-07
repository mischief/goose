#include "ucontext_i.h"

.text

.global makecontext
makecontext:
  movl    4(%esp), %eax   /* ucontext pointer */
  movl    8(%esp), %ecx  /* function pointer */

  /* load instruction pointer */
  movl    %ecx, oEIP(%eax)

  /* compute new stack pointer */
  movl    oSS_SP(%eax), %edx /* ss_sp */
  addl    oSS_SIZE(%eax), %edx /* ss_size */
  /* (%edx) is now our stack. */

  /* put next uc_link on stack */
  movl    oLINK(%eax), %ecx
  movl    %ecx, -4(%edx)

  /* Remember the number of parameters for the exit handler since
     it has to remove them.  We store the number in the EBX register
     which the function we will call must preserve.  */
  movl    12(%esp), %ecx
  movl    %ecx, oEBX(%eax)

  /* Make room on the new stack for the parameters.  */
  negl    %ecx
  leal    -8(%edx,%ecx,4), %edx
  negl    %ecx
  /* Store the future stack pointer.  */
  movl    %edx, oESP(%eax)

  /* Copy all the parameters.  */
  jecxz   2f
1:
  movl    12(%esp,%ecx,4), %eax
  movl    %eax, (%edx,%ecx,4)
  decl    %ecx
  jnz     1b
2:

  /* If the function we call returns we must continue with the
     context which is given in the uc_link element.  To do this
     set the return address for the function the user provides
     to a little bit of helper code which does the magic (see
     below).  */
  movl $exitcode, (%edx)
  /* 'makecontext' returns no value.  */
  ret

  /* This is the helper code which gets called if a function which
     is registered with 'makecontext' returns.  In this case we
     have to install the context listed in the uc_link element of
     the context 'makecontext' manipulated at the time of the
     'makecontext' call.  If the pointer is NULL the process must
     terminate.  */
exitcode:
  /* This removes the parameters passed to the function given to
     'makecontext' from the stack.  EBX contains the number of
     parameters (see above).  */
  leal  (%esp,%ebx,4), %esp

  popl  %eax      /* This is the next context.  */
  testl %eax, %eax
  je  2f      /* If it is zero exit.  */

  pushl %eax
  call  setcontext
  /* If this returns (which can happen if the syscall fails) we'll
     exit the program with the return error value (-1).  */

2:
  pushl   %eax
  call    exit
  /* The 'exit' call should never return.  In case it does cause
     the process to terminate.  */
  hlt

