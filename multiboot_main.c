#include <u.h>
#include <libc.h>
#include <multiboot.h>
#include <ucontext.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

extern unsigned long magic;
extern unsigned long mbd;

multiboot_info_t mbi;

extern void runtime_printf(const char *, ...);

static const char delim[] = " \f\n\r\t\v";

int gooseargc;
char **gooseargv;
char *parsedargv[10];
static char *null_args[] = {"kernel", 0};

void
goose_argv(void)
{
  if(CHECK_FLAG (mbi.flags, 2)) {
    char *cl = (char *) mbi.cmdline;
    unsigned cllen = strlen(cl);
    char *toks[1 + cllen];
    size_t ntoks = 0;
    char *tok;
    int i;

    for (tok = strtok(cl, delim); tok; tok = strtok(0, delim))
      toks[ntoks++] = tok;

    if(ntoks == 0) {
      goto nocmdline;
    }

    for(i = 0; i < ntoks && i < 9; i++) {
      parsedargv[i] = toks[i];
    }
    parsedargv[i+1] = 0;
    gooseargc = ntoks;
    gooseargv = parsedargv;
 } else {
nocmdline:
    gooseargc = 1;
    gooseargv = null_args;
 }
}

extern int monitor_clear(void) __asm__ ("runtime.MonitorClear");

static ucontext_t ctx[3];

static void
f1(int i)
{
  runtime_printf("start f1 %x\n", i);
  swapcontext(&ctx[1], &ctx[2]);
  runtime_prints("finish f1\n");
}


static void
f2(int i)
{
  runtime_printf("start f2 %x\n", i);
  swapcontext(&ctx[2], &ctx[1]);
  runtime_prints("finish f2\n");
}

void
check_context(void)
{
  char st1[2048];
  char st2[2048];

  getcontext(&ctx[1]);
  ctx[1].uc_stack.ss_sp = st1;
  ctx[1].uc_stack.ss_size = sizeof st1;
  ctx[1].uc_link = &ctx[0];
  makecontext(&ctx[1], (void (*)(void))f1, 1, 0x1BADDEAD);

  getcontext(&ctx[2]);
  ctx[2].uc_stack.ss_sp = st2;
  ctx[2].uc_stack.ss_size = sizeof st2;
  ctx[2].uc_link = &ctx[1];
  makecontext(&ctx[2], (void (*)(void))f2, 1, 0x2BADDEAD);

  swapcontext(&ctx[0], &ctx[2]);
}

void
goose_main(void)
{
  monitor_clear();
  //check_context();

  if (magic != MULTIBOOT_BOOTLOADER_MAGIC) {
    runtime_printf("Invalid magic number: %x\n", (unsigned) magic);
    return;
  }

  mbi = *((multiboot_info_t *)mbd);

 /* Print out the flags. */
 runtime_printf ("flags = %x\n", (unsigned) mbi.flags);

 /* Are mem_* valid? */
 if (CHECK_FLAG (mbi.flags, 0))
   runtime_printf ("mem_lower = %dKB, mem_upper = %dKB\n",
           (unsigned) mbi.mem_lower, (unsigned) mbi.mem_upper);

 /* Is boot_device valid? */
 if (CHECK_FLAG (mbi.flags, 1))
   runtime_printf ("boot_device = %x\n", (unsigned) mbi.boot_device);

 /* Is the command line passed? */
 if (CHECK_FLAG (mbi.flags, 2))
   runtime_printf ("cmdline = %s\n", (char *) mbi.cmdline);

 /* Are mods_* valid? */
 if (CHECK_FLAG (mbi.flags, 3))
   {
     multiboot_module_t *mod;
     int i;

     runtime_printf ("mods_count = %d, mods_addr = %x\n",
             (int) mbi.mods_count, (int) mbi.mods_addr);
     for (i = 0, mod = (multiboot_module_t *) mbi.mods_addr;
          i < mbi.mods_count;
          i++, mod++)
       runtime_printf (" mod_start = %x, mod_end = %x, cmdline = %s\n",
               (unsigned) mod->mod_start,
               (unsigned) mod->mod_end,
               (char *) mod->cmdline);
   }

 /* Bits 4 and 5 are mutually exclusive! */
 if (CHECK_FLAG (mbi.flags, 4) && CHECK_FLAG (mbi.flags, 5))
   {
     runtime_printf ("Both bits 4 and 5 are set.\n");
     return;
   }

 /* Is the symbol table of a.out valid? */
 if (CHECK_FLAG (mbi.flags, 4))
   {
     multiboot_aout_symbol_table_t *multiboot_aout_sym = &(mbi.u.aout_sym);

     runtime_printf ("multiboot_aout_symbol_table: tabsize = %0x, "
             "strsize = %x, addr = %x\n",
             (unsigned) multiboot_aout_sym->tabsize,
             (unsigned) multiboot_aout_sym->strsize,
             (unsigned) multiboot_aout_sym->addr);
   }

 /* Is the section header table of ELF valid? */
 if (CHECK_FLAG (mbi.flags, 5))
   {
     multiboot_elf_section_header_table_t *multiboot_elf_sec = &(mbi.u.elf_sec);

     runtime_printf ("multiboot_elf_sec: num = %d, size = %x,"
             " addr = %x, shndx = %x\n",
             (unsigned) multiboot_elf_sec->num, (unsigned) multiboot_elf_sec->size,
             (unsigned) multiboot_elf_sec->addr, (unsigned) multiboot_elf_sec->shndx);
   }

 /* Are mmap_* valid? */
 if (CHECK_FLAG (mbi.flags, 6))
   {
     multiboot_memory_map_t *mmap;

     runtime_printf ("mmap_addr = %x, mmap_length = %x\n",
             (unsigned) mbi.mmap_addr, (unsigned) mbi.mmap_length);
     for (mmap = (multiboot_memory_map_t *) mbi.mmap_addr;
          (unsigned long) mmap < mbi.mmap_addr + mbi.mmap_length;
          mmap = (multiboot_memory_map_t *) ((unsigned long) mmap
                                   + mmap->size + sizeof (mmap->size)))
       runtime_printf (" size = %x, base_addr = %X,"
               " length = %X, type = %d\n",
               (unsigned) mmap->size,
               mmap->addr,
               mmap->len,
               (unsigned) mmap->type);
   }

  goose_argv();
  init_descriptor_tables();
  main(gooseargc, gooseargv);
}
