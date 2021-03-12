
//specify the entry address of the program
ENTRY(nomain)

OUTPUT_FORMAT(elf32-i386)
OUTPUT_ARCH(i386:i386)

SECTIONS
{
    . = 0x0100000;

    .text :
    {
        *(.multiboot)
        *(.test*)
        *(.rodata)
    }

    .data :
    {
        start_ctors = .;
        KEEP(*(.init_array));
        KEEP(*(SORT_BY_INIT_PRIORITY(.init_array.*)));
        ent_ctors = .;

        *(.data)

    }

    .bss
    {
        *(.bss)
    }

    //segment we no longer needed, for example comment parts.
    /DISCARD/ :
    {
        *(.fini_array*)
        *(.comment)
    }
}