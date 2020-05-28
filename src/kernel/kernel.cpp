
#include <kernel/kernel.h>
#include <kernel/terminal.h>
#include <stdint.h>

void kernel_main() {
    Terminal::Initialize();

    for(uint8_t x = (uint8_t)'A'; x <= (uint8_t)'z'; x++) {
        Terminal::WriteString((char *) &x);
    }
}

