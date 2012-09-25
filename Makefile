### Build arams

CC_CROSS = i586-elf-gcc
LD_CROSS = i586-elf-ld
GO_CROSS = i586-elf-gccgo
PREPROC = $(CC_CROSS) -E -x c -P
CC = gcc
LD = ld
ASM = nasm -f elf
CFLAGS_CROSS = -Werror -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
GOFLAGS_CROSS = -static  -Werror -nostdlib -nostartfiles -nodefaultlibs 
INCLUDE_DIRS = -I.

### Sources

CORE_SOURCES = loader.s.o goose.go.o

SOURCE_OBJECTS = $(CORE_SOURCES)

 
### Targets

all: kernel.img

clean:
	rm -f $(SOURCE_OBJECTS) $(TEST_EXECS) kernel.bin kernel.img

boot-nogrub: kernel.bin
	qemu-system-i386 -kernel kernel.bin

boot: kernel.img
	qemu-system-i386 -fda kernel.img 

### Rules

%.s.o: %.s
	$(ASM) $(INCLUDE_DIRS) -o $@ $<

%.go.o: %.go
	$(GO_CROSS) $(GOFLAGS_CROSS) -o $@ -c $<

kernel.bin: $(SOURCE_OBJECTS)
	$(LD_CROSS) -T link.ld -o kernel.bin $(SOURCE_OBJECTS)
 
kernel.img: kernel.bin
	cp floppy.img.template kernel.img
	mcopy -i kernel.img -/ grub/ ::/
	mcopy -i kernel.img kernel.bin ::/
