### Build params

TOPDIR := $(shell pwd)
export TOPDIR

include Makefile.inc

### Sources

CORE_SOURCES = \
	loader.o \
	multiboot_main.o \
	gdt.o \
	interrupt.o \
	main.o \

LIBS = 386/lib/libgo.a 386/lib/libc.a 386/lib/libm.a

SOURCE_OBJECTS = $(CORE_SOURCES)

### Targets

all: kernel.img

clean:
	rm -f *.o
	rm -f $(LIBS)
	rm -f kernel.exe kernel.bin kernel.img
	cd sys/src; make clean

boot-nogrub: kernel.bin
	qemu-system-i386 -kernel kernel.bin

boot: kernel.img
	qemu-system-i386 -fda kernel.img

### Rules

386/lib/libm.a:
	cd sys/src/libm; make

386/lib/libc.a:
	cd sys/src/libc; make

386/lib/libgo.a:
	cd sys/src/libgo; make

kernel.exe: $(LIBS) $(SOURCE_OBJECTS)
	$(LD_CROSS) $(GOFLAGS_CROSS) $(GO_IMPORT_DIRS) -Wl,-T,link.ld -L386/lib -o $@ $(SOURCE_OBJECTS) -lgo -lgcc -lm -lc

kernel.img: kernel.exe
	strip -o kernel.bin kernel.exe
	cp floppy.img.template kernel.img
	mcopy -i kernel.img -/ grub/ ::/
	mcopy -i kernel.img kernel.bin ::/

