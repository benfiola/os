
#include <kernel/kernel.h>
#include <kernel/pmm.h>
#include <kernel/terminal.h>
#include <stdint.h>

void kernel_main() {
    Terminal_initialize();
    PMM_initialize();
    Terminal_writeString("Done");
}

