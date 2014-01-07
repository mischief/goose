#include "ucontext_i.h"

.text

.global setcontext
setcontext:
  /* Load address of the context data structure.  */
  movl    4(%esp), %eax

  /* segments */
  mov     oGS(%eax), %gs
  mov     oFS(%eax), %fs
  mov     oES(%eax), %es
  mov     oDS(%eax), %ds

  /* Load the new stack pointer.  */
  movl    oESP(%eax), %ecx
  /* Make room for 8 registers and the return address.  We will load
     the values from the stack.  */
  subl    $36, %ecx

  /* Move the values of all the 32-bit registers (except ESP) on
     the stack.  This happens in the form the 'popa' instruction
     expects it.  Before this block put the address of the code
     to execute.  */
  movl    oEDI(%eax), %ebx
  movl    oESI(%eax), %edx
  movl    oEBP(%eax), %esi
  movl    oEBX(%eax), %edi
  movl    %ebx, (%ecx)
  movl    %edx, 4(%ecx)
  movl    %esi, 8(%ecx)
  movl    %edi, 16(%ecx)
  movl    oEDX(%eax), %ebx
  movl    oECX(%eax), %edx
  movl    oEAX(%eax), %esi
  movl    oEIP(%eax), %edi
  movl    %ebx, 20(%ecx)
  movl    %edx, 24(%ecx)
  movl    %esi, 28(%ecx)
  movl    %edi, 32(%ecx)

  /* Set the new stack address.  The stack points now to the block
     we put the register content in.  */
  movl    %ecx, %esp
  /* Restore the register content.  */
  popa
  /* The following 'ret' will pop the addres of the code and jump
     to it.  */

  ret

