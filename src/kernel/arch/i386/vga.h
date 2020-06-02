#ifndef KERNEL_VGA_H
#define KERNEL_VGA_H

#include <kernel/terminal.h>
#include <stdint-gcc.h>

enum VGA_Color {
    VGA_Color_Black = 0x0,
    VGA_Color_Blue = 0x1,
    VGA_Color_Green = 0x2,
    VGA_Color_Cyan = 0x3,
    VGA_Color_Red = 0x4,
    VGA_Color_Magenta = 0x5,
    VGA_Color_Brown = 0x6,
    VGA_Color_LightGray = 0x7,
    VGA_Color_DarkGray = 0x8,
    VGA_Color_LightBlue = 0x9,
    VGA_Color_LightGreen = 0xA,
    VGA_Color_LightCyan = 0xB,
    VGA_Color_LightRed = 0xC,
    VGA_Color_LightMagenta = 0xD,
    VGA_Color_Yellow = 0xE,
    VGA_Color_White = 0xF,
};

static uint16_t* VGA_buffer = (uint16_t *) 0xB8000;

uint16_t VGA_createData(enum VGA_Color fg, enum VGA_Color bg, char c);
enum VGA_Color VGA_convertTerminalColor(enum Terminal_Color c);



#endif