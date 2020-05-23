/*
 * This is the GNU linker script. For documentation, see
 * https://sourceware.org/binutils/docs-2.21/ld/Scripts.html
 */

/* Define the kernel entry point symbol */
ENTRY(_start)

SECTIONS {
    /* Start loading after 1MB as GRUB, memory-mapped I/O,
     * and BIOS own the first 1MB
     */
    . = 1M;

    .text BLOCK(4K) : ALIGN (4K)
    {
        *(.multiboot)
        *(.text)
    }

    .rodata BLOCK(4K) : ALIGN (4K)
    {
        *(.rodata*)
    }

    .data BLOCK(4K) : ALIGN (4K)
    {
        *(.data)
    }

    .bss BLOCK(4K) : ALIGN (4K)
    {
        *(COMMON)
        *(.bss)
    }
}