#include <stddef.h>
#include <string.h>
#include "vga.h"

static Terminal::State state;

void Terminal::Initialize() {
    state.height = 25;
    state.width = 80;
    state.x = 0;
    state.y = 0;
    state.bgColor = Terminal::Black;
    state.fgColor = Terminal::White;
}

void Terminal::SetBgColor(Terminal::Color bgColor) {
    state.bgColor = bgColor;
}

Terminal::Color Terminal::GetBgColor() {
    return state.bgColor;
}

void Terminal::SetFgColor(Terminal::Color fgColor){
    state.fgColor = fgColor;
}

Terminal::Color Terminal::GetFgColor() {
    return state.fgColor;
}

void ScreenShiftUp() {
    for(int y = 1; y < state.height; y++) {
        for(int x = 0; x < state.width; x++) {
            uint16_t curr_position = (y * state.width) + x;
            uint16_t new_position = curr_position - state.width;
            VGA::buffer[new_position] = VGA::buffer[curr_position];
        }
    }
    for(int x = 0; x < state.width; x++) {
        uint16_t curr_position = ( ( state.height - 1) * state.width) + x;
        VGA::buffer[curr_position] = (uint16_t) 0;
    }
}

void CursorAdvanceLine() {
    state.x = 0;
    state.y += 1;
    if(state.y >= state.height) {
        ScreenShiftUp();
        state.y -= 1;
    }
}

void CursorAdvance() {
    state.x += 1;
    if(state.x > state.width) {
        state.x = state.x - state.width;
        CursorAdvanceLine();
    }
}

void Terminal::WriteChar(char c) {
    uint16_t position = (state.width * state.y) + state.x;

    VGA::Color fg = VGA::TranslateTerminalColor(state.fgColor);
    VGA::Color bg = VGA::TranslateTerminalColor(state.bgColor);

    VGA::buffer[position] = VGA::CreateTextData(fg, bg, c);
    CursorAdvance();
}

void Terminal::WriteString(char *line) {
    for(size_t x = 0; x < strlen(line); x++) {
        WriteChar(line[x]);
    }
    CursorAdvanceLine();
}


