CMAKE_MINIMUM_REQUIRED(VERSION 3.10)
PROJECT(os C CXX ASM-ATT)

SET(ARCH "i386")

SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
SET(CMAKE_CXX_STANDARD 11)

ADD_SUBDIRECTORY(src/kernel)
ADD_SUBDIRECTORY(src/libc)

# on install, prepare the sysroot.
INSTALL(
    TARGETS kernel-bin
    DESTINATION ${CMAKE_SYSROOT}/boot
)
INSTALL(
    TARGETS libc-user
    DESTINATION ${CMAKE_SYSROOT}/usr/local/lib
)
INSTALL(
    FILES src/grub/grub.cfg
    DESTINATION ${CMAKE_SYSROOT}/boot/grub/
)

# expose a target to copy kernel/libc headers
ADD_CUSTOM_TARGET(
        copy-headers
        COMMAND mkdir -p ${CMAKE_SYSROOT}/usr/include/
        COMMAND chmod a+w -R ${CMAKE_SYSROOT}/usr/include
        COMMAND cp -R ${CMAKE_CURRENT_SOURCE_DIR}/src/kernel/include/* ${CMAKE_SYSROOT}/usr/include/
        COMMAND cp -R ${CMAKE_CURRENT_SOURCE_DIR}/src/libc/include/* ${CMAKE_SYSROOT}/usr/include/
        COMMAND chmod a-w -R ${CMAKE_SYSROOT}/usr/include/
)

# expose a target to build an .iso from the sysroot
ADD_CUSTOM_TARGET(
        iso
        COMMAND grub-mkrescue -o ${CMAKE_INSTALL_PREFIX}/os.iso ${CMAKE_SYSROOT}
)