CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(os C CXX ASM-ATT)

SET(ARCH "i386")

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(src/kernel)
ADD_SUBDIRECTORY(src/libc)

# install the multiboot kernel image to the boot directory
INSTALL(
    TARGETS kernel-bin
    DESTINATION boot
)
# install the grub menu entry pointing to the kernel image
INSTALL(
        FILES src/grub/grub.cfg
        DESTINATION boot/grub/
)
# install userspace headers to usr/local/include
INSTALL(
    DIRECTORY src/kernel/include src/libc/include
    DESTINATION usr/local/include/
)
INSTALL(
    TARGETS libc-user
    DESTINATION usr/local/lib
)

ADD_CUSTOM_TARGET(clion_install)
