//
// Created by benfiola on 5/24/20.
//

#ifndef OS_STRING_H
#define OS_STRING_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

int memcmp(const void *str1, const void *str2, size_t n);
void *memcpy(void *dest, const void *src, size_t n);
void *memmove(void *str1, const void *str2, size_t n);
void *memset(void *str, int c, size_t n);
size_t strlen(const char *str);

#ifdef __cplusplus
}
#endif

#endif //OS_STRING_H
