#ifndef KERNEL_VGA_H
#define KERNEL_VGA_H

#include <kernel/terminal.h>
#include <stdint-gcc.h>

namespace VGA {
    enum Color {
        Black = 0x0,
        Blue = 0x1,
        Green = 0x2,
        Cyan = 0x3,
        Red = 0x4,
        Magenta = 0x5,
        Brown = 0x6,
        LightGray = 0x7,
        DarkGray = 0x8,
        LightBlue = 0x9,
        LightGreen = 0xA,
        LightCyan = 0xB,
        LightRed = 0xC,
        LightMagenta = 0xD,
        Yellow = 0xE,
        White = 0xF,
    };

    static uint16_t* buffer = (uint16_t *) 0xB8000;

    uint16_t CreateTextData(Color fg, Color bg, char c);
    Color TranslateTerminalColor(Terminal::Color c);
}


#endif