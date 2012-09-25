GO-OSe
======
GO-OSe is an experiment in low level microprocessor programming using the Go
programming language <golang.org>. Goose implements a basic x86 asm bootstrap
which drops into kernel.Kmain() in Go, and provides rudimentary text io.

Why?
----
Because I wanted to see if it was possible. Turns out it is, but not without
making sacrifices. Go's lack of pointer arithmetic means you remain fairly
dependant on asm to do things that would otherwise be trivial in C.
Because we're creating our own environment for Go, a lot of it's features
must be implemented manually using asm, or at the very least defined as
noop to allow compilation.
tldr: It's fun, but not worth it.

Building
--------
Goose requires gccgo, and a cross compiler toolchain may have to be built
if the host os is 64-bit. More info on that here: http://wiki.osdev.org/GCC_Cross-Compiler
If compiling from source, remember to add go to gcc's --enable-languages
config option.

![goose](https://raw.github.com/tgascoigne/goose/master/goose.png) 
