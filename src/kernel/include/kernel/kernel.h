#ifndef KERNEL_KERNEL_H
#define KERNEL_KERNEL_H 1

#include "multiboot.h"

void kernel_main(multiboot_info_t* mbd, unsigned int magic);

#endif