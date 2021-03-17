/* The bootloader will look at this image and start execution
 * at the symbol designated as the entry point. */
ENTRY(_start)

/* Tell where the various sections of the object files will be put
 * in the final kernel image. */
SECTIONS
{
    /* Begin putting sections at 1 MiB, a conventional place for kernels
     * to be loaded at by the bootloader. */
    . = 0x00100000;

    _kernel_start = .;
    .multiboot.data ALIGN(4K) : {
        /* I don't understand why I need this padding, but if I omit
         * it then the multiboot header ends up in the wrong place... */
        SHORT(0xaaaa)
        *(.multiboot.data)
    }

    .multiboot.text ALIGN(4K) : {
        *(.multiboot.text)
    }

    . += 0x0C000000;

    .text ALIGN(4K) : AT (ADDR(.text) - 0xC0000000)
    {
        *(.text)
    }

    /* Read-only data. */
    .rodata ALIGN(4K) : AT (ADDR(.rodata) - 0xC0000000)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data ALIGN(4K) : AT (ADDR(.data) - 0xC0000000)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss ALIGN(4K) : AT (ADDR(.bss) - 0xC0000000)
    {
        *(COMMON)
        *(.bss)
        *(.bootstrap_stack)
    }

    /* The compiler may produce other sections, by default it will put them
     * in a section with the same name. Simply add stuff here as needed. */

    _kernel_end= .;
}
