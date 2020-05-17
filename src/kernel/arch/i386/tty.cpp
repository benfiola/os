//
// Created by benfiola on 5/17/20.
//

#include <kernel/tty.h>
#include "vga.h"

class Terminal {
    private:
        int Row;
        int Column;
        int Color;
        void WriteChar(char s);
        void WriteString(char* s, size_t size);
    public:
        Terminal();

        void Write(char* s);

        void SetColor(int color);
        int GetColor();

        void SetRow(int row);
        int GetRow();

        void SetColumn(int column);
        int GetColumn();
};

Terminal::Terminal() {
    Row = 0;
    Column = 0;
    Color = VGAColors.White;
}

Terminal::WriteChar(char* s) {

}

Terminal::WriteString(char* s, int size) {
    for (int i = 0; i < size; i++) {
        WriteChar(s[i]);
    }
}

Terminal::Write(char* s) {
    WriteString(s, str)
}

Terminal::SetColor(int color) {
    Color = color;
}

Terminal::GetColor() {
    return Color;
}

Terminal::SetRow(int row) {
    Row = row;
}

Terminal::GetRow() {
    return Row;
}

Terminal::SetColumn(int column) {
    Column = column;
}

Terminal::GetColumn() {
    return Column;
}
