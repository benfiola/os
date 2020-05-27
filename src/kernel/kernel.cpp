
#include <kernel/kernel.h>
#include <kernel/terminal.h>

void kernel_main() {
    Terminal::Initialize();

    for(int x = 0; x < 80; x++) {
        Terminal::Write((char *) "hello");
    }
}
