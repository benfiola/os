//
// Created by benfiola on 5/17/20.
//

#ifndef OS_TTY_H
#define OS_TTY_H

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

#endif //OS_TTY_H
