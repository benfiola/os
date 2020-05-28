
#include "vga.h"

uint16_t VGA::CreateTextData(Color fg, Color bg, char data) {
    return bg << 12 | (fg << 8) | data;
}

VGA::Color VGA::TranslateTerminalColor(Terminal::Color c) {
    switch(c) {
        case Terminal::White: return VGA::White;
        case Terminal::Black: return VGA::Black;
        default: return VGA::Black;
    }
}
