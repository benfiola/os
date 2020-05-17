#!/bin/sh
export HOST="i686-elf"
export ARCH="i386"
CWD=$(pwd)
export BUILD_DIRECTORY="${CWD}/build"
export INSTALL_DIRECTORY="${CWD}/install"

export SYSROOT="${INSTALL_DIRECTORY}/sysroot"

export AR="${HOST}-ar"
export AS="${HOST}-as"
export CC="${HOST}-gcc"
export CC="${CC} --sysroot=${SYSROOT}"
export CC="${CC} --isystem=${INCLUDEDIR}"
export CXX="${HOST}-g++"
export CXX="${CXX} --sysroot=${SYSROOT}"
export CXX="${CXX} --isystem=${INCLUDEDIR}"

export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include
export BUILD_DIRECTORY="${CWD}/build"
export DESTDIR="${INSTALL_DIRECTORY}"


export CFLAGS='-O2 -g'
export CPPFLAGS
