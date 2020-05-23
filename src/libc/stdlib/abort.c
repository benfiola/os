//
// Created by benfiola on 5/25/20.
//

#include <stdio.h>
#include <stdlib.h>

__attribute__((__noreturn__))
void abort(void) {

#if defined(libc_kernel)
    printf("kernel:abort");
#else
    printf("abort");
#endif

while (1) { }
__builtin_unreachable();

}
