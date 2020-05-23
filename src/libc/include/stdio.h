//
// Created by benfiola on 5/24/20.
//

#ifndef OS_STDIO_H
#define OS_STDIO_H

#ifdef __cplusplus
extern "C" {
#endif

int printf(const char *format, ...);
int putchar(int c);
int puts(const char *str);

#ifdef __cplusplus
}
#endif

#endif //OS_STDIO_H
