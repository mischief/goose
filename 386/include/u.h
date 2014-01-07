#define nil             ((void*)0)
#define NULL            ((void*)0)
typedef unsigned short  ushort;
typedef unsigned char   uchar;
typedef unsigned long   ulong;
typedef unsigned int    uint;
typedef signed char     schar;
typedef long long       vlong;
typedef unsigned long long uvlong;
typedef unsigned long   uintptr __attribute__ ((mode (pointer)));
typedef unsigned long   usize;
typedef uint            Rune;
typedef union FPdbleword FPdbleword;
typedef long            jmp_buf[2];
#define JMPBUFSP        0
#define JMPBUFPC        1
#define JMPBUFDPC       0
typedef unsigned int    mpdigit;        /* for /sys/include/mp.h */
typedef unsigned char   u8int;
typedef unsigned short  u16int;
typedef unsigned int    u32int;
typedef unsigned long long u64int;

typedef uintptr uintptr_t;
typedef unsigned long long uint64;
typedef long unsigned int size_t;
typedef uint64 uint64_t;

#define va_start(v,l) __builtin_va_start(v,l)
#define va_arg(v,l)   __builtin_va_arg(v,l)
#define va_end(v)     __builtin_va_end(v)
#define va_copy(d,s)  __builtin_va_copy(d,s)
typedef __builtin_va_list va_list;
