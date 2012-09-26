global loader                           ; making entry point visible to linker
global magic                            ; we will use this in kmain
global mbd                              ; we will use this in kmain

global __go_register_gc_roots
global __go_runtime_error

global __unsafe_get_addr

extern go.kernel.Kmain                            ; kmain is defined in kmain.cpp

MODULEALIGN equ  1<<0                   ; align loaded modules on page boundaries
MEMINFO     equ  1<<1                   ; provide memory map
FLAGS       equ  MODULEALIGN | MEMINFO  ; this is the Multiboot 'flag' field
MAGIC       equ  0x1BADB002             ; 'magic number' lets bootloader find the header
CHECKSUM    equ -(MAGIC + FLAGS)        ; checksum required

section .text

align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

; reserve initial kernel stack space
STACKSIZE equ 0x4000                    ; that's 16k.

loader:
    mov  esp, stack + STACKSIZE         ; set up the stack
    mov  [magic], eax                   ; Multiboot magic number
    mov  [mbd], ebx                     ; Multiboot info structure

    call go.kernel.Kmain                          ; call kernel proper

    cli
.hang:
    hlt                                 ; halt machine should kernel return
    jmp  .hang

__unsafe_get_addr:
    push ebp
    mov ebp,esp
    mov eax, [ebp+8]
    mov  esp,ebp
    pop  ebp
    ret

__go_runtime_error:
__go_register_gc_roots:
    ret

section .bss

align 4
stack: resb STACKSIZE                   ; reserve 16k stack on a doubleword boundary
magic: resd 1
mbd:   resd 1
