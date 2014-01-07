#ifndef MULTIBOOT_H
#define MULTIBOOT_H

#define MULTIBOOT_SEARCH		8192
#define MULTIBOOT_HEADER_MAGIC		0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC  0x2BADB002
#define MULTIBOOT_UNSUPPORTED		0x0000fffc
#define MULTIBOOT_MOD_ALIGN		0x00001000
#define MULTIBOOT_INFO_ALIGN		0x00000004
#define MULTIBOOT_PAGE_ALIGN		0x00000001
#define MULTIBOOT_MEMORY_INFO		0x00000002
#define MULTIBOOT_VIDEO_MODE		0x00000004
#define MULTIBOOT_AOUT_KLUDGE		0x00010000
#define MULTIBOOT_INFO_MEMORY		0x00000001
#define MULTIBOOT_INFO_BOOTDEV		0x00000002
#define MULTIBOOT_INFO_CMDLINE		0x00000004
#define MULTIBOOT_INFO_MODS		0x00000008
#define MULTIBOOT_INFO_AOUT_SYMS	0x00000010
#define MULTIBOOT_INFO_ELF_SHDR		0x00000020
#define MULTIBOOT_INFO_MEM_MAP		0x00000040
#define MULTIBOOT_INFO_DRIVE_INFO	0x00000080
#define MULTIBOOT_INFO_CONFIG_TABLE	0x00000100
#define MULTIBOOT_INFO_BOOT_LOADER_NAME 0x00000200
#define MULTIBOOT_INFO_APM_TABLE	0x00000400
#define MULTIBOOT_INFO_VIDEO_INFO	0x00000800

#include <u.h>

struct multiboot_header {
  u32int magic;
  u32int flags;
  u32int checksum;
  
  u32int header_addr;
  u32int load_addr;
  u32int load_end_addr;
  u32int bss_end_addr;
  u32int entry_addr;
  
  u32int mode_type;
  u32int width;
  u32int height;
  u32int depth;
};

struct multiboot_aout_symbol_table {
  u32int tabsize;
  u32int strsize;
  u32int addr;
  u32int reserved;
};

typedef struct multiboot_aout_symbol_table multiboot_aout_symbol_table_t;

struct multiboot_elf_section_header_table {
  u32int num;
  u32int size;
  u32int addr;
  u32int shndx;
};

typedef struct multiboot_elf_section_header_table multiboot_elf_section_header_table_t;

struct multiboot_info {
  u32int flags;
  u32int mem_lower;
  u32int mem_upper;
  u32int boot_device;
  u32int cmdline;
  u32int mods_count;
  u32int mods_addr;

  union {
    multiboot_aout_symbol_table_t aout_sym;
    multiboot_elf_section_header_table_t elf_sec;
  } u;

  u32int mmap_length;
  u32int mmap_addr;
  u32int drives_length;
  u32int drives_addr;
  u32int config_table;
  u32int boot_loader_name;
  u32int apm_table;

  u32int vbe_control_info;
  u32int vbe_mode_info;
  u16int vbe_mode;
  u16int vbe_interface_seg;
  u16int vbe_interface_off;
  u16int vbe_interface_len;
};

typedef struct multiboot_info multiboot_info_t;

struct multiboot_mmap_entry {
  u32int size;
  u64int addr;
  u64int len;

  /* why is this in the middle of the struct? */
  #define MULTIBOOT_MEMORY_AVAILABLE	1
  #define MULTIBOOT_MEMORY_RESERVED	2
  
  u32int type;
  
};

typedef struct multiboot_mmap_entry multiboot_memory_map_t;

struct multiboot_mod_list {
  u32int mod_start;
  u32int mod_end;
  u32int cmdline;
  u32int pad;
};

typedef struct multiboot_mod_list multiboot_module_t;

#endif /* !MULTIBOOT_H */

