include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.13.0)
project(cross-compiler)

set(TARGET i686-elf)
set(NCPU 8)

get_filename_component(INSTALL_DIRECTORY ./install ABSOLUTE)
get_filename_component(BINUTILS_DIRECTORY ./binutils ABSOLUTE)
get_filename_component(GCC_DIRECTORY ./gcc ABSOLUTE)

ExternalProject_Add(
    binutils

    TMP_DIR ${BINUTILS_DIRECTORY}/tmp
    STAMP_DIR ${BINUTILS_DIRECTORY}/stamp
    DOWNLOAD_DIR ${BINUTILS_DIRECTORY}/src
    SOURCE_DIR ${BINUTILS_DIRECTORY}/src
    BINARY_DIR ${BINUTILS_DIRECTORY}/build
    INSTALL_DIR ${INSTALL_DIRECTORY}

    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
    LOG_UPDATE 1
    LOG_DOWNLOAD 1
    LOG_TEST 1

    CONFIGURE_COMMAND <SOURCE_DIR>/configure --target=${TARGET} --prefix=${INSTALL_DIRECTORY} --with-sysroot --disable-nls --disable-werror
    BUILD_COMMAND make -j${NCPU}
    INSTALL_COMMAND make install
)

ExternalProject_Add(
    gcc

    DEPENDS binutils

    TMP_DIR ${GCC_DIRECTORY}/tmp
    STAMP_DIR ${GCC_DIRECTORY}/stamp
    DOWNLOAD_DIR ${GCC_DIRECTORY}/src
    SOURCE_DIR ${GCC_DIRECTORY}/src
    BINARY_DIR ${GCC_DIRECTORY}/build
    INSTALL_DIR ${INSTALL_DIRECTORY}

    LOG_CONFIGURE 1
    LOG_BUILD 1
    LOG_INSTALL 1
    LOG_UPDATE 1
    LOG_DOWNLOAD 1
    LOG_TEST 1

    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E env PATH=${INSTALL_DIRECTORY}:$ENV{PATH} <SOURCE_DIR>/configure --target=${TARGET} --prefix=${INSTALL_DIRECTORY} --disable-nls --enable-languages=c,c++ --without-headers
    BUILD_COMMAND ${CMAKE_COMMAND} -E env PATH=${INSTALL_DIRECTORY}:$ENV{PATH} make all-gcc all-target-libgcc -j${NCPU}
    INSTALL_COMMAND make install-gcc install-target-libgcc
)
