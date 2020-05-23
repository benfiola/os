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
# define headers visibility
TARGET_INCLUDE_DIRECTORIES(
        libc-user
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
# specify ifdef indicating compiling for user-mode
TARGET_COMPILE_DEFINITIONS(libc-user PRIVATE libc_user)

# define a kernel-mode libc library
ADD_LIBRARY(
        libc-kernel
        ${LIBC_SOURCES}
)
# define headers visibility
TARGET_INCLUDE_DIRECTORIES(
        libc-kernel
        PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)
TARGET_LINK_LIBRARIES(libc-kernel kernel)

# specify ifdef indicating compiling for kernel-mode
TARGET_COMPILE_DEFINITIONS(libc-kernel PRIVATE libc_kernel)
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ffreestanding")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding")
