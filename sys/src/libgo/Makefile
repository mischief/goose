SUFFIXES = .c .go .gox .o .obj .lo .a

include $(TOPDIR)/Makefile.inc

OBJS :=	\
	runtime/go-assert-interface.o \
	runtime/go-assert.o \
	runtime/go-append.o \
	runtime/go-byte-array-to-string.o \
	runtime/go-caller.o \
	runtime/go-callers.o \
	runtime/go-can-convert-interface.o \
	runtime/go-check-interface.o \
	runtime/go-construct-map.o \
	runtime/go-convert-interface.o \
	runtime/go-copy.o \
	runtime/go-defer.o \
	runtime/go-eface-compare.o \
	runtime/go-getgoroot.o \
	runtime/go-int-array-to-string.o \
	runtime/go-int-to-string.o \
	runtime/go-interface-compare.o \
	runtime/go-main.o \
	runtime/go-make-slice.o \
	runtime/go-map-delete.o \
	runtime/go-map-index.o \
	runtime/go-map-range.o \
	runtime/go-memcmp.o \
	runtime/go-nanotime.o \
	runtime/go-new-map.o \
	runtime/go-new.o \
	runtime/go-now.o \
	runtime/go-panic.o \
	runtime/go-print.o \
	runtime/go-recover.o \
	runtime/go-reflect-call.o \
	runtime/go-reflect-map.o \
	runtime/go-rune.o \
	runtime/go-runtime-error.o \
	runtime/go-strcmp.o \
	runtime/go-string-to-byte-array.o \
	runtime/go-string-to-int-array.o \
	runtime/go-strplus.o \
	runtime/go-strslice.o \
	runtime/go-traceback.o \
	runtime/go-trampoline.o \
	runtime/go-type-complex.o \
	runtime/go-type-eface.o \
	runtime/go-type-error.o \
	runtime/go-type-float.o \
	runtime/go-type-identity.o \
	runtime/go-type-interface.o \
	runtime/go-type-string.o \
	runtime/go-typedesc-equal.o \
	runtime/go-typestring.o \
	runtime/go-unsafe-new.o \
	runtime/go-unsafe-newarray.o \
	runtime/go-unsafe-pointer.o \
	runtime/go-unwind.o \
	runtime/chan.o \
	runtime/iface.o \
	runtime/lfstack.o \
	runtime/lock_futex.o \
	runtime/malloc.o \
	runtime/map.o \
	runtime/mcache.o \
	runtime/mcentral.o \
	runtime/mem.o \
	runtime/mfinal.o \
	runtime/mfixalloc.o \
	runtime/mgc0.o \
	runtime/mheap.o \
	runtime/monitor.o \
	runtime/mprof.o \
	runtime/msize.o \
	runtime/panic.o \
	runtime/parfor.o \
	runtime/print.o \
	runtime/proc.o \
	runtime/reflect.o \
	runtime/runtime.o \
	runtime/sema.o \
	runtime/string.o \
	runtime/stub.o \
	runtime/thread-goose.o \
	runtime/thread.o \
	runtime/time.o \
	runtime/yield.o

libgo_go_objs := \
	runtime-go.o \
	syscall.o \
	errors.o \
	os.o \
	reflect.o \
  strconv.o \
	sync/atomic.o \
	sync/atomic_c.o \
	sync.o \
	math.o \
	unicode.o \
	unicode/utf8.o \
	time.o \
	io.o \
	fmt.o \

libgo_DATA := \
	runtime.gox \
	syscall.gox \
	errors.gox \
	os.gox \
	reflect.gox \
	strconv.gox \
	sync/atomic.o \
	sync.gox \
	math.gox \
	unicode.gox \
	unicode/utf8.gox \
	time.gox \
	io.gox \
	fmt.gox

DATA := \
	$(libgo_DATA)

LIBADD := \
	$(libgo_go_objs)

.PHONY: all
all: libgo.a $(DATA)

libgo.a: $(OBJS) $(LIBADD)
	$(AR_CROSS) $(ARFLAGS) $(TOPDIR)/386/lib/$@ $^

go_runtime_files = \
	go/runtime/compiler.go \
	go/runtime/debug.go \
	go/runtime/error.go \
	go/runtime/extern.go \
	go/runtime/mem.go \
	go/runtime/monitor.go \
	go/runtime/softfloat64.go \
	go/runtime/type.go \
	version.go

.PHONY: version.go
version.go:
	rm -f version.go
	echo "package runtime" >> version.go
	echo 'const defaultGoroot = "$(TOPDIR)"' >> version.go
	echo 'const theVersion = "'`$(CC) --version | sed 1q`'"' >> version.go
	echo 'const theGoarch = "'$(GOARCH)'"' >> version.go
	echo 'const theGoos = "'$(GOOS)'"' >> version.go

go_errors_files = \
	go/errors/errors.go

go_syscall_files = \
	go/syscall/syscall.go \
	go/syscall/stub.go
#	go/syscall/env_unix.go \

go_os_files = \
	go/os/env.go \
	go/os/error.go \
	go/os/types.go \
	go/os/file.go \
	go/os/file_unix.go \
	go/os/proc.go

go_reflect_files = \
	go/reflect/deepequal.go \
	go/reflect/makefunc.go \
	go/reflect/type.go \
	go/reflect/value.go

go_strconv_files = \
	go/strconv/atob.go \
	go/strconv/atof.go \
	go/strconv/atoi.go \
	go/strconv/decimal.go \
	go/strconv/extfloat.go \
	go/strconv/ftoa.go \
	go/strconv/isprint.go \
	go/strconv/itoa.go \
	go/strconv/quote.go

go_sync_atomic_c_files = \
	go/sync/atomic/atomic.c

go_sync_atomic_files = \
	go/sync/atomic/doc.go

go_sync_files = \
	go/sync/cond.go \
	go/sync/mutex.go \
	go/sync/once.go \
	go/sync/race0.go \
	go/sync/runtime.go \
	go/sync/rwmutex.go \
	go/sync/waitgroup.go

go_math_files = \
	go/math/abs.go \
	go/math/acosh.go \
	go/math/asin.go \
	go/math/asinh.go \
	go/math/atan.go \
	go/math/atanh.go \
	go/math/atan2.go \
	go/math/bits.go \
	go/math/cbrt.go \
	go/math/const.go \
	go/math/copysign.go \
	go/math/dim.go \
	go/math/erf.go \
	go/math/exp.go \
	go/math/expm1.go \
	go/math/floor.go \
	go/math/frexp.go \
	go/math/gamma.go \
	go/math/hypot.go \
	go/math/j0.go \
	go/math/j1.go \
	go/math/jn.go \
	go/math/ldexp.go \
	go/math/lgamma.go \
	go/math/log.go \
	go/math/log1p.go \
	go/math/log10.go \
	go/math/logb.go \
	go/math/mod.go \
	go/math/modf.go \
	go/math/nextafter.go \
	go/math/pow.go \
	go/math/pow10.go \
	go/math/remainder.go \
	go/math/signbit.go \
	go/math/sin.go \
	go/math/sincos.go \
	go/math/sinh.go \
	go/math/sqrt.go \
	go/math/tan.go \
	go/math/tanh.go \
	go/math/unsafe.go

go_unicode_files = \
	go/unicode/casetables.go \
	go/unicode/digit.go \
	go/unicode/graphic.go \
	go/unicode/letter.go \
	go/unicode/tables.go

go_unicode_utf8_files = \
	go/unicode/utf8/utf8.go

go_time_files = \
	go/time/format.go \
	go/time/sleep.go \
	go/time/tick.go \
	go/time/time.go \
	go/time/zoneinfo.go \
	go/time/zoneinfo_goose.go

go_io_files = \
	go/io/multi.go \
	go/io/io.go \
	go/io/pipe.go

go_fmt_files = \
	go/fmt/doc.go \
	go/fmt/format.go \
	go/fmt/print.go \
	go/fmt/scan.go

runtime-go.o: $(go_runtime_files)
	$(BUILDPACKAGE)

-include errors.o.dep
errors.o.dep: $(go_errors_files)
	$(BUILDDEPS)
errors.o: $(go_errors_files)
	$(BUILDPACKAGE)

-include syscall.o.dep
syscall.o.dep: $(go_syscall_files)
	$(BUILDDEPS)
syscall.o: $(go_syscall_files)
	$(BUILDPACKAGE)

-include os.o.dep
os.o.dep: $(go_os_files)
	$(BUILDDEPS)
os.o: $(go_os_files)
	$(BUILDPACKAGE)

-include reflect.o.dep
reflect.o.dep: $(go_reflect_files)
	$(BUILDDEPS)
reflect.o: $(go_reflect_files)
	$(BUILDPACKAGE)

-include strconv.o.dep
strconv.o.dep: $(go_strconv_files)
	$(BUILDDEPS)
strconv.o: $(go_strconv_files)
	$(BUILDPACKAGE)

sync/atomic.o.dep: $(go_sync_atomic_files)
	$(BUILDDEPS)
sync/atomic.o: $(go_sync_atomic_files)
	$(BUILDPACKAGE)

#atomic.o.dep: $(go_errors_files)
#	$(BUILDDEPS)
sync/atomic_c.o: $(go_sync_atomic_c_files)
	$(CC_CROSS) $(CFLAGS_CROSS) $(GO_IMPORT_DIRS) $(INCLUDE_DIRS) -Iruntime -c -o $@ $^

-include sync.o.dep
sync.o.dep: $(go_sync_files)
	$(BUILDDEPS)
sync.o: $(go_sync_files)
	$(BUILDPACKAGE)

-include math.o.dep
math.o.dep: $(go_math_files)
	$(BUILDDEPS)
math.o: $(go_math_files)
	$(BUILDPACKAGE)

-include unicode.o.dep
unicode.o.dep: $(go_unicode_files)
	$(BUILDDEPS)
unicode.o: $(go_unicode_files)
	$(BUILDPACKAGE)
unicode/utf8.o.dep: $(go_unicode_utf8_files)
	$(BUILDDEPS)
unicode/utf8.o: $(go_unicode_utf8_files)
	$(BUILDPACKAGE)

-include time.o.dep
time.o.dep: $(go_time_files)
	$(BUILDDEPS)
time.o: $(go_time_files)
	$(BUILDPACKAGE)

-include io.o.dep
io.o.dep: $(go_io_files)
	$(BUILDDEPS)
io.o: $(go_io_files)
	$(BUILDPACKAGE)

-include fmt.o.dep
fmt.o.dep: $(go_fmt_files)
	$(BUILDDEPS)
fmt.o: $(go_fmt_files)
	$(BUILDPACKAGE)

runtime.gox: runtime-go.o
	$(BUILDGOX)
syscall.gox: syscall.o
	$(BUILDGOX)
errors.gox: errors.o
	$(BUILDGOX)
os.gox: os.o
	$(BUILDGOX)
reflect.gox: reflect.o
	$(BUILDGOX)
strconv.gox: strconv.o
	$(BUILDGOX)
sync/atomic.gox: sync/atomic.o
	$(BUILDGOX)
sync.gox: sync.o
	$(BUILDGOX)
math.gox: math.o
	$(BUILDGOX)
unicode.gox: unicode.o
	$(BUILDGOX)
unicode/utf8.gox: unicode/utf8.o
	$(BUILDGOX)
io.gox: io.o
	$(BUILDGOX)
fmt.gox: fmt.o
	$(BUILDGOX)

goc2c: goc2c.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $<

#.PHONY: runtime/malloc.c
#runtime/malloc.c: runtime/malloc.goc goc2c
#	./goc2c $< > $@.tmp
#	mv -f $@.tmp $@

.PHONY: runtime/%.c
runtime/%.c: runtime/%.goc goc2c
	rm -f $@
	./goc2c $< > $@.tmp
	mv -f $@.tmp $@

.PHONY: clean
clean:
	rm -f version.go
	rm -f goc2c
	rm -f *.dep */*.dep
	rm -f *.gox */*.gox
	rm -f *.o */*.o runtime/*.o
	rm -f $(LIBADD)
	rm -f $(TOPDIR)/386/lib/libgo.a

