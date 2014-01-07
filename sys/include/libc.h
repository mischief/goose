#define nelem(x)  (sizeof(x)/sizeof((x)[0]))
#define offsetof(s, m)  (ulong)(&(((s*)0)->m))
//#define assert(x) if(x){}else _assert("x")

/* mem routines */
extern void* memccpy(void*, void*, int, ulong);
extern void* memset(void*, int, ulong);
extern int memcmp(void*, void*, ulong);
extern void* memcpy(void*, void*, ulong);
extern void* memmove(void*, void*, ulong);
extern void* memchr(void*, int, ulong);

/* string routines */
int strcmp(const char * s1, const char * s2);
size_t strlen(const char *s);
char *strncpy(char *s1, const char *s2, size_t n);
char *strrchr(const char * s, int c);
char *strtok(char *, const char *);

/* memory */
void *malloc(size_t size);
void free(void *);

/* io.c */
void outb(u16int port, u8int value);
u8int inb(u16int port);
u16int inw(u16int port);

/* time.c */
struct timeval {
  long tv_sec;
  long long tv_usec;
};

void gettimeofday(struct timeval *, void *);

void exit(int) __attribute__ ((noreturn));
void abort(void) __attribute__ ((noreturn));

