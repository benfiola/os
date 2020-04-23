include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

cmake_minimum_required(VERSION 3.13.0)
project(cross_compiler)

if(NOT DEFINED BUILD_DIRECTORY)
    message(FATAL_ERROR "Build directory undefined")
endif(NOT DEFINED BUILD_DIRECTORY)
if(NOT DEFINED TARGET)
    message(FATAL_ERROR "Target undefined")
endif(NOT DEFINED TARGET)

set(INSTALL_DIRECTORY ${BUILD_DIRECTORY}/install)
set(NCPU 8)

get_filename_component(BINUTILS_SRC ./binutils ABSOLUTE)
get_filename_component(BINUTILS_BUILD ${BUILD_DIRECTORY}/binutils ABSOLUTE)
get_filename_component(GCC_SRC ./gcc ABSOLUTE)
get_filename_component(GCC_BUILD ${BUILD_DIRECTORY}/gcc ABSOLUTE)


ExternalProject_Add(
    binutils

    TMP_DIR ${BINUTILS_BUILD}/tmp
    STAMP_DIR ${BINUTILS_BUILD}/stamp
    DOWNLOAD_DIR ${BINUTILS_SRC}
    SOURCE_DIR ${BINUTILS_SRC}
    BINARY_DIR ${BINUTILS_BUILD}/build
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

    TMP_DIR ${GCC_BUILD}/tmp
    STAMP_DIR ${GCC_BUILD}/stamp
    DOWNLOAD_DIR ${GCC_SRC}
    SOURCE_DIR ${GCC_SRC}
    BINARY_DIR ${GCC_BUILD}/build
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

add_custom_target(
    cross_compiler
    DEPENDS binutils gcc
)
