#ifndef KERNEL_TERMINAL_H
#define KERNEL_TERMINAL_H 1

namespace Terminal {
    enum Color {
        Black = 0,
        White = 1
    };

    struct State {
        Color fgColor;
        Color bgColor;
        int x;
        int y;
        int height;
        int width;
    };

    void Initialize();

    void SetBgColor(Color c);
    Color GetBgColor();

    void SetFgColor(Color c);
    Color GetFgColor();

    void WriteChar(char word);
    void WriteString(char* word);
}

#endif
