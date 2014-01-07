the os files in the top level should probably be in the go runtime package somewhere.

sys/src/libgo/runtime/monitor.c implements the vga console.

multiboot_main.c calls into sys/src/libgo/runtime/go-main.c, which calls back to main.go, eventually.

goroutines are very broken.

the malloc implementation is very poor. see sys/src/libc/alloc.c

