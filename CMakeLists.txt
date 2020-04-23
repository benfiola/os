cmake_minimum_required(VERSION 3.0)

# set the project name and version
project(os VERSION 1.0)

set(TARGET i686-elf)
get_filename_component(ROOT_BUILD_DIRECTORY ./build ABSOLUTE)

set(BUILD_DIRECTORY ${ROOT_BUILD_DIRECTORY}/cross_compiler)
add_subdirectory(src/cross_compiler)
unset(BUILD_DIRECTORY)

set(BUILD_DIRECTORY ${ROOT_BUILD_DIRECTORY}/kernel)
add_subdirectory(src/kernel)
unset(BUILD_DIRECTORY)

set(BUILD_DIRECTORY ${ROOT_BUILD_DIRECTORY}/libc)
add_subdirectory(src/libc)
unset(BUILD_DIRECTORY)

# i686-elf-as boot.s -o boot.o
# i686-elf-g++ -c kernel.c++ -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
# i686-elf-g++ -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc