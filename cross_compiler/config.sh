#!/bin/sh -e
CWD=$(pwd)
export BUILD_DIRECTORY="${CWD}/build"
export INSTALL_DIRECTORY="${CWD}/dist"
export SOURCE_BINUTILS_DIRECTORY="${CWD}/src/binutils"

# having build issues with binutils-2_34 due to this bug (potentially)
# https://sourceware.org/pipermail/gdb-patches/2020-March/166453.html
# temporarily using gcc 9.2.0 with binutils 2.32
export SOURCE_BINUTILS_TAG="binutils-2_32"

export SOURCE_BINUTILS_URL="git://sourceware.org/git/binutils-gdb.git"
export SOURCE_GCC_DIRECTORY="${CWD}/src/gcc"
export SOURCE_GCC_TAG="releases/gcc-9.2.0"
export SOURCE_GCC_URL="git://gcc.gnu.org/git/gcc.git"
export TARGET="i686-elf"
NCPU="$(nproc)"
export NCPU
export PREFIX="$PREFIX"
