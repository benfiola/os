#!/bin/sh -e
export BUILD_DIRECTORY="$(pwd)/build"
export INSTALL_DIRECTORY="$(pwd)/dist"
export SOURCE_BINUTILS_DIRECTORY="$(pwd)/src/binutils"

# having build issues with binutils-2_34 due to this bug (potentially)
# https://sourceware.org/pipermail/gdb-patches/2020-March/166453.html
# temporarily using gcc 9.2.0 with binutils 2.32
export SOURCE_BINUTILS_TAG="binutils-2_32"

export SOURCE_BINUTILS_URL="git://sourceware.org/git/binutils-gdb.git"
export SOURCE_GCC_DIRECTORY="$(pwd)/src/gcc"
export SOURCE_GCC_TAG="releases/gcc-9.2.0"
export SOURCE_GCC_URL="git://gcc.gnu.org/git/gcc.git"
export TARGET="i686-elf"
export NCPU="$(nproc)"
export PREFIX="$PREFIX"
