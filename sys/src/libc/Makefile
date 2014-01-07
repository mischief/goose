include $(TOPDIR)/Makefile.inc

OBJS := \
	abort.o \
	alloc.o \
	errno.o \
	exit.o \
	gettimeofday.o \
	io.o \
	memchr.o \
	memcmp.o \
  memcpy.o \
	memmove.o \
	memset.o \
	strcmp.o \
	strlen.o \
	strncpy.o \
	strrchr.o \
	strtok.o \
	386/getcontext.o \
	386/makecontext.o \
	386/setcontext.o \
	386/swapcontext.o


libc.a: $(OBJS)
	$(AR_CROSS) $(ARFLAGS) $(TOPDIR)/386/lib/$@ $^

%.o: %.s
	$(AS_CROSS) -o $@ $<

.PHONY: clean
clean:
	rm -f $(TOPDIR)/386/lib/libc.a $(OBJS)

