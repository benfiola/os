CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

FUNCTION(LOAD_PROFILE ARCH)
    INCLUDE(arch/${ARCH}/flags.cmake)
ENDFUNCTION(LOAD_PROFILE ARCH)

LOAD_PROFILE(${ARCH})

FILE(GLOB_RECURSE LIBC_SOURCES *.c *.cpp *.s)

# define a user-mode libc library
ADD_LIBRARY(
        libc-user
        ${LIBC_SOURCES}
)
# specify ifdef indicating compiling for user-mode
TARGET_COMPILE_DEFINITIONS(libc-user PRIVATE libc_user)

# define a kernel-mode libc library
ADD_LIBRARY(
        libc-kernel
        ${LIBC_SOURCES}
)
# specify ifdef indicating compiling for kernel-mode
TARGET_COMPILE_DEFINITIONS(libc-kernel PRIVATE libc_kernel)

# unfortunately TARGET_COMPILE_OPTIONS apples to assemblers as well.
# this is the alternative.
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding")
