
#include <kernel/kernel.h>
#include <kernel/pmm.h>
#include <kernel/terminal.h>

void kernel_main(multiboot_info_t* mbd, unsigned int magic) {
    Terminal_initialize();

    if((mbd->flags & 1) == 0) {
        Terminal_writeString("Non-continguous memory region detected");
    }
    PMM_initialize();
    Terminal_writeString("Done");
}

