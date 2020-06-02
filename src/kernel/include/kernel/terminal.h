#ifndef KERNEL_TERMINAL_H
#define KERNEL_TERMINAL_H 1

enum Terminal_Color {
    Terminal_Color_Black = 0,
    Terminal_Color_White = 1
};

struct Terminal_State {
    enum Terminal_Color fgColor;
    enum Terminal_Color bgColor;
    int x;
    int y;
    int height;
    int width;
};

void Terminal_initialize();

void Terminal_setBgColor(enum Terminal_Color c);
enum Terminal_Color Terminal_getBgColor();

void Terminal_setFgColor(enum Terminal_Color c);
enum Terminal_Color Terminal_getFgColor();

void Terminal_writeChar(char word);
void Terminal_writeString(char* word);


#endif
