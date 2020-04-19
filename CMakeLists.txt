cmake_minimum_required(VERSION 3.0)

# set the project name and version
project(os VERSION 1.0)

# i686-elf-as boot.s -o boot.o
# i686-elf-g++ -c kernel.c++ -o kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
# i686-elf-g++ -T linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc
