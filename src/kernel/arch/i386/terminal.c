#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include "vga.h"

static struct Terminal_State state;

void Terminal_initialize() {
    state.height = 25;
    state.width = 80;
    state.x = 0;
    state.y = 0;
    state.bgColor = Terminal_Color_Black;
    state.fgColor = Terminal_Color_White;

    puts("Terminal: Initialized");
}

void Terminal_setBgColor(enum Terminal_Color bgColor) {
    state.bgColor = bgColor;
}

enum Terminal_Color Terminal_getBgColor() {
    return state.bgColor;
}

void Terminal_setFgColor(enum Terminal_Color fgColor){
    state.fgColor = fgColor;
}

enum Terminal_Color Terminal_getFgColor() {
    return state.fgColor;
}

void Terminal_shiftScreenUp() {
    for(int y = 1; y < state.height; y++) {
        for(int x = 0; x < state.width; x++) {
            uint16_t curr_position = (y * state.width) + x;
            uint16_t new_position = curr_position - state.width;
            VGA_buffer[new_position] = VGA_buffer[curr_position];
        }
    }
    for(int x = 0; x < state.width; x++) {
        uint16_t curr_position = ( ( state.height - 1) * state.width) + x;
        VGA_buffer[curr_position] = (uint16_t) 0;
    }
}

void Terminal_cursorAdvanceLine() {
    state.x = 0;
    state.y += 1;
    if(state.y >= state.height) {
        Terminal_shiftScreenUp();
        state.y -= 1;
    }
}

void Terminal_cursorAdvance() {
    state.x += 1;
    if(state.x > state.width) {
        state.x = state.x - state.width;
        Terminal_cursorAdvanceLine();
    }
}

void Terminal_writeChar(char c) {
    if(c == '\n') {
        Terminal_cursorAdvanceLine();
        return;
    }

    uint16_t position = (state.width * state.y) + state.x;

    enum VGA_Color fg = VGA_convertTerminalColor(state.fgColor);
    enum VGA_Color bg = VGA_convertTerminalColor(state.bgColor);

    VGA_buffer[position] = VGA_createData(fg, bg, c);
    Terminal_cursorAdvance();
}
