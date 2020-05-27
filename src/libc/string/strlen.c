
#include <string.h>

size_t strlen(const char *str) {
    int size = 0;
    while(str[size] != '\0') {
        size = size + 1;
    }
    return size;
}
