ENTRY (loader)

SECTIONS
{
    . = 1M;

    .text BLOCK(4k) : ALIGN (4k)
    {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4k) : ALIGN (4k)
    {
        *(.rodata)
    }

    .data BLOCK(4k) : ALIGN (4k)
    {
        *(.data)
    }

    .go_export BLOCK(4k) : ALIGN(4k)
    {
        *(.go_export)
    }

    .bss BLOCK(4k) : ALIGN (4k)
    {
        sbss = .;
        *(COMMON)
        *(.bss)
        ebss = .;
    }

    end = .;
}
