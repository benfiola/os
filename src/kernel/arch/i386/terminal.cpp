
#include <kernel/terminal.h>
#include "vga.h"

void Terminal::Initialize() {
    VGA::Initialize();
}

void Terminal::Write(char* word) {
    VGA::WriteLine(word);
}
