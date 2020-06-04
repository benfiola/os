//
// Created by benfiola on 5/25/20.
//

#include <stdio.h>

#if defined(libc_kernel)
#include <kernel/terminal.h>
#endif

int putchar(int c) {
#if defined(libc_kernel)
    Terminal_writeChar(c);
    return c;
#else
    return -1;
#endif
}
