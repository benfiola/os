
#include "vga.h"

uint16_t VGA_createData(enum VGA_Color fg, enum VGA_Color bg, char data) {
    return bg << 12 | (fg << 8) | data;
}

enum VGA_Color VGA_convertTerminalColor(enum Terminal_Color c) {
    switch(c) {
        case Terminal_Color_White: return VGA_Color_White;
        case Terminal_Color_Black: return VGA_Color_Black;
        default: return VGA_Color_Black;
    }
}
