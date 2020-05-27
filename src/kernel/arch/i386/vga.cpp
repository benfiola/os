
#include "vga.h"
#include <string.h>

static VGA::Screen screen;


void VGA::Initialize() {
    screen.cursor.fg = VGA::White;
    screen.cursor.bg = VGA::Black;
    screen.cursor.x = 0;
    screen.cursor.y = 0;
    screen.buffer = (uint16_t *) 0xB8000;
    screen.height = 25;
    screen.width = 80;
}

void VGA::SetColor(VGA::Color fg, VGA::Color bg) {
    screen.cursor.fg = fg;
    screen.cursor.bg = bg;
}

void ScreenShiftUp() {
    for(int y = 1; y < screen.height; y++) {
        for(int x = 0; x < screen.width; x++) {
            uint16_t curr_position = (y * screen.width) + x;
            uint16_t new_position = curr_position - screen.width;
            screen.buffer[new_position] = screen.buffer[curr_position];
        }
    }
    for(int x = 0; x < screen.width; x++) {
        uint16_t curr_position = ( ( screen.height - 1) * screen.width) + x;
        screen.buffer[curr_position] = (uint16_t) 0;
    }
}

void CursorAdvanceLine() {
    screen.cursor.x = 0;
    screen.cursor.y += 1;
    if(screen.cursor.y >= screen.height) {
        ScreenShiftUp();
        screen.cursor.y -= 1;
    }
}

void CursorAdvance() {
    screen.cursor.x += 1;
    if(screen.cursor.x > screen.width) {
        screen.cursor.x = screen.cursor.x - screen.width;
        CursorAdvanceLine();
    }
}

void VGA::WriteChar(char c) {
    uint16_t position = (screen.width * screen.cursor.y) + screen.cursor.x;
    uint16_t value = (screen.cursor.bg << 12) | (screen.cursor.fg << 8) | c;
    screen.buffer[position] = value;
    CursorAdvance();
}

void VGA::WriteLine(char *line) {
    for(size_t x = 0; x < strlen(line); x++) {
        WriteChar(line[x]);
    }
    CursorAdvanceLine();
}

