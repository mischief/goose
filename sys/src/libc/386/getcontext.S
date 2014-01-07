#include "ucontext_i.h"

.text

.global getcontext
getcontext:
  /* ucontext pointer */
  movl    4(%esp), %eax

  /* eax is not preserved. */
  movl    $0, 64(%eax)

  /* registers */
  movl    %ecx, oECX(%eax)
  movl    %edx, oEDX(%eax)
  movl    %edi, oEDI(%eax)
  movl    %esi, oESI(%eax)
  movl    %ebp, oEBP(%eax)
  movl    (%esp), %ecx    /* store eip */
  movl    %ecx, oEIP(%eax)
  leal    4(%esp), %ecx
  movl    %ecx, oESP(%eax)  /* store esp */
  movl    %ebx, oEBX(%eax)

  /* segments */
  xorl    %edx, %edx
  movw    %gs,  %dx
  movl    %edx, oGS(%eax)

  xorl    %edx, %edx
  movw    %fs,  %dx
  movl    %edx, oFS(%eax)

  xorl    %edx, %edx
  movw    %es,  %dx
  movl    %edx, oES(%eax)

  xorl    %edx, %edx
  movw    %ds,  %dx
  movl    %edx, oDS(%eax)

  xorl    %edx, %edx
  movw    %cs,  %dx
  movl    %edx, oCS(%eax)

  /* flags */
  pushfl                /* push EFLAGS */
  popl    oEFLAGS(%eax) /* store flags */

  /* return value */
  movl     $0, %eax

  ret

  /* stack pointer */
  mov     %ss, 92(%eax)
  movl    %ebp, oSS_SP(%eax) /* ss_sp */
  movl    (%ebp), %ebx
  movl    %ebx, oSS_BP(%eax) /* ss_bp */

