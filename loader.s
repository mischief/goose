global loader                           ; making entry point visible to linker
 
extern go.kernel.Kmain                            ; kmain is defined in kmain.cpp
 
section .text
 
align 4

; reserve initial kernel stack space
STACKSIZE equ 0x4000                    ; that's 16k.
 
loader:
    mov  esp, stack + STACKSIZE         ; set up the stack
 
    call go.kernel.Kmain                          ; call kernel proper
 
    cli
.hang:
    hlt                                 ; halt machine should kernel return
    jmp  .hang
 
section .bss
 
align 4
stack: resb STACKSIZE                   ; reserve 16k stack on a doubleword boundary
