#ifndef KERNEL_VGA_H
#define KERNEL_VGA_H

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

    struct Cursor {
        Color fg;
        Color bg;
        int x;
        int y;
    };

    struct Screen {
        uint16_t* buffer;
        uint16_t height;
        uint16_t width;
        Cursor cursor;
    };

    void Initialize();
    void SetColor(Color fg, Color bg);
    void WriteChar(char c);
    void WriteLine(char* line);
}


#endif