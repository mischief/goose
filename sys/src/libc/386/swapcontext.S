#include "ucontext_i.h"

.text

.global swapcontext
swapcontext:
  /* Load address of the context data structure we save in.  */
  movl  4(%esp), %eax

  /* Return value of swapcontext.  EAX is the only register whose
     value is not preserved.  */
  movl  $0, oEAX(%eax)

  /* Save the 32-bit register values and the return address.  */
  movl  %ecx, oECX(%eax)
  movl  %edx, oEDX(%eax)
  movl  %edi, oEDI(%eax)
  movl  %esi, oESI(%eax)
  movl  %ebp, oEBP(%eax)
  movl  (%esp), %ecx
  movl  %ecx, oEIP(%eax)
  leal  4(%esp), %ecx
  movl  %ecx, oESP(%eax)
  movl  %ebx, oEBX(%eax)

  /* save segments */
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

  /* Load address of the context data structure we have to load.  */
  movl  8(%esp), %ecx

  /* EAX was modified, reload it.  */
  movl  8(%esp), %eax

  /* restore segments */
  mov     oGS(%eax), %gs
  mov     oFS(%eax), %fs
  mov     oES(%eax), %es
  mov     oDS(%eax), %ds

  /* Load the new stack pointer.  */
  movl  oESP(%eax), %ecx
  /* Make room for 8 registers and the return address.  We will load
     the values from the stack.  */
  subl  $36, %ecx

  /* Move the values of all the 32-bit registers (except ESP) on
     the stack.  This happens in the form the 'popa' instruction
     expects it.  Before this block put the address of the code
     to execute.  */
  movl  oEDI(%eax), %ebx
  movl  oESI(%eax), %edx
  movl  oEBP(%eax), %esi
  movl  oEBX(%eax), %edi
  movl  %ebx, (%ecx)
  movl  %edx, 4(%ecx)
  movl  %esi, 8(%ecx)
  movl  %edi, 16(%ecx)
  movl  oEDX(%eax), %ebx
  movl  oECX(%eax), %edx
  movl  oEAX(%eax), %esi
  movl  oEIP(%eax), %edi
  movl  %ebx, 20(%ecx)
  movl  %edx, 24(%ecx)
  movl  %esi, 28(%ecx)
  movl  %edi, 32(%ecx)

  /* Set the new stack address.  The stack points now to the block
     we put the register content in.  */
  movl  %ecx, %esp
  /* Restore the register content.  */
  popa
  /* The following 'ret' will pop the addres of the code and jump
     to it.  */

  ret

