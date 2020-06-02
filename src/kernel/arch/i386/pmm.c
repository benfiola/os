
#include <kernel/pmm.h>
#include <kernel/terminal.h>

void bios_function();

void PMM_initialize() {
    Terminal_writeString("Initializing PMM here");
    bios_function();
}