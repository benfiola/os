
#include <kernel/kernel.h>
#include <kernel/pmm.h>
#include <kernel/terminal.h>
#include <stdio.h>

void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
    Terminal_initialize();
    if(magic != MULTIBOOT_BOOTLOADER_MAGIC ) {
        puts("ERROR: Kernel: Multiboot header does not match");
    }
    PMM_initialize(mbd);
}

