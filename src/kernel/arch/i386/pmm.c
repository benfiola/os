
#include <kernel/pmm.h>
#include <stdio.h>
#include <kernel/multiboot.h>

void PMM_initialize(multiboot_info_t* mbd) {
    puts("PMM: Initializing");
    unsigned int useMmem = mbd->flags & (1 << 6);
    unsigned int useMem = mbd->flags & (1);
    if(useMmem) {
        puts("PMM: Using multiboot mmem_* fields to determine memory region data");
        unsigned int total = mbd->mmap_length;
        multiboot_memory_map_t* curr = (multiboot_memory_map_t*) mbd->mmap_addr;
        while(total > 0) {
            printf("%f", 80372.1239185123);
            printf("Address: %#200.200x, Length: %i, Type: %i", curr->addr, curr->len, curr->type);
            unsigned int size = curr->size + sizeof(curr->size);
            total -= size;
            curr = (multiboot_memory_map_t*) (((unsigned int) curr) + size);
        }
    } else if(useMem) {
        puts("PMM: Using multiboot mem_* fields to determine memory region data");
    } else {
        puts("ERROR: PMM: Unable to determine memory region data");
    }
    puts("PMM: Initialized");

}