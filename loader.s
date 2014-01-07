;
; Adapted from osdev.org's Bare Bones tutorial http://wiki.osdev.org/Bare_Bones
;

global loader
global magic
global mbd

global gdt_flush
global idt_flush

extern goose_main

; Multiboot stuff
MODULEALIGN equ  1<<0
MEMINFO     equ  1<<1
FLAGS       equ  MODULEALIGN | MEMINFO
MAGIC       equ  0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)


section .multiboot
align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

STACKSIZE equ 0x4000  ; Define our stack size at 16k

section .text
loader:
    mov  esp, stack + STACKSIZE ; Setup stack pointer

    mov  [magic], eax
    mov  [mbd], ebx

    ; fpu init early on
    fninit

    sti

    call goose_main

    cli
.exit:
.hang:
    hlt
    jmp  .hang

gdt_flush:
   mov eax, [esp+4]  ; Get the pointer to the GDT, passed as a parameter.
   lgdt [eax]        ; Load the new GDT pointer

   mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
   mov ds, ax        ; Load all data segment selectors
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush   ; 0x08 is the offset to our code segment: Far jump!
.flush:
   ret

idt_flush:
   mov eax, [esp+4]  ; Get the pointer to the IDT, passed as a parameter. 
   lidt [eax]        ; Load the IDT pointer.
   ret

section .bss
align 4
magic: resd 1
mbd:   resd 1
stack: resb STACKSIZE   ; Reserve 16k for stack

