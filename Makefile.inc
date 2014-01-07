# vim: set filetype=make

GOOS=goose
GOARCH=386
O=8
AS_CROSS = i586-elf-as
CC_CROSS = i586-elf-gcc
LD_CROSS = i586-elf-gccgo
GO_CROSS = i586-elf-gccgo
OBJCOPY = i586-elf-objcopy
AR_CROSS = i586-elf-ar
ARFLAGS = cru
PREPROC = $(CC_CROSS) -E -x c -P
CC = gcc
LD = ld
ASM = nasm -f elf
CFLAGS_CROSS = -g -O1 -Werror -nostdinc -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fplan9-extensions
GOFLAGS_CROSS = -static -g -O1 -Werror -nostdlib -nostartfiles -nodefaultlibs 
INCLUDE_DIRS = -I. -I$(TOPDIR)/386/include -I$(TOPDIR)/sys/include
GO_IMPORT_DIRS = -I$(TOPDIR)/sys/src/libgo

MKDIR_P = mkdir -p

BUILDPACKAGE = \
	$(MKDIR_P) $(@D); \
	f=`echo $^ | sed -e 's/[^ ]*\.gox//g'`; \
	$(GO_CROSS) $(GO_IMPORT_DIRS) $(INCLUDE_DIRS) -c -fgo-pkgpath=`echo $@ | sed -e 's/.o$$//' -e 's/-go$$//'` -o $@ $$f
#$(LTGOCOMPILE) -I . -c -fgo-pkgpath=`echo $@ | sed -e 's/.lo$$//' -e 's/-go$$//'` -o $@ $$files

# How to build a .gox file from a .lo file.
BUILDGOX = \
	f=`echo $< | sed -e 's/.lo$$/.o/'`; \
	$(OBJCOPY) -j .go_export $$f $@.tmp && mv -f $@.tmp $@

BUILDDEPS = \
	$(MKDIR_P) $(@D); \
	$(SHELL) $(TOPDIR)/godeps.sh `echo $@ | sed -e 's/.dep$$//'` $^ > $@.tmp; \
	mv -f $@.tmp $@

%.o: %.s
	$(ASM) $(INCLUDE_DIRS) -o $@ $<

# preprocessed assembly
%.o: %.S
	$(CC_CROSS) -o $@ -c $<

%.o: %.c
	$(CC_CROSS) $(CFLAGS_CROSS) $(INCLUDE_DIRS) -o $@ -c $<

%.o: %.go
	$(GO_CROSS) $(GOFLAGS_CROSS) $(INCLUDE_DIRS) $(GO_IMPORT_DIRS) -o $@ -c $<

%.gox: %.o
	$(BUILDGOX)

