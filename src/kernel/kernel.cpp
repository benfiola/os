
#include <kernel/kernel.h>
#include <kernel/terminal.h>
#include <stdint.h>

void kernel_main() {
    Terminal::Initialize();

    for(uint8_t x = (int)'A'; x <= (int)'z'; x++) {
        char c = (char)x;
        Terminal::Write(&c);
    }
}

