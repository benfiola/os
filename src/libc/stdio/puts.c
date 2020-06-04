//
// Created by benfiola on 5/25/20.
//

#include <stdio.h>

int puts(const char *str) {
    while(*str != '\0') {
        putchar(*str);
        str = str + 1;
    }
    putchar('\n');
    return 1;
}
