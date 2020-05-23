#!/bin/sh -e

PWD="$(pwd)"
SCRIPT_DIRECTORY="$(dirname "$(realpath "$0")")"
BINUTILS_SOURCE_URL="${BINUTILS_SOURCE_URL:-https://mirrors.ocf.berkeley.edu/gnu/binutils/binutils-2.32.tar.gz}"
GCC_SOURCE_URL="${GCC_SOURCE_URL:-http://www.netgull.com/gcc/releases/gcc-9.2.0/gcc-9.2.0.tar.gz}"
TARGET="${TARGET:-i686-elf}"
SOURCE_DIRECTORY="${SCRIPT_DIRECTORY}/source"
BUILD_DIRECTORY="${SCRIPT_DIRECTORY}/build"
INSTALL_DIRECTORY="${SCRIPT_DIRECTORY}/install"
NUM_CPUS="${NUM_CPUS:-$(nproc)}"


activate() {
  PATH="$(path):${PATH}"
  echo "PATH=$PATH"
}

check() {
  if [ ! -e "$(path)/${TARGET}-as" ]; then
    exit 1
  fi
  if [ ! -e "$(path)/${TARGET}-gcc" ]; then
    exit 1
  fi
}

path() {
  echo "${INSTALL_DIRECTORY}/bin"
}

target() {
  echo "${TARGET}"
}

build() {
  ## checkout
  # derive source folders and filenames
  BINUTILS_SOURCE_FILE_NAME="$(basename "${BINUTILS_SOURCE_URL}")"
  BINUTILS_SOURCE_FOLDER_NAME="$(basename "${BINUTILS_SOURCE_FILE_NAME}" .tar.gz)"
  BINUTILS_SOURCE_FILE="${SOURCE_DIRECTORY}/${BINUTILS_SOURCE_FILE_NAME}"
  BINUTILS_SOURCE_DIRECTORY="${SOURCE_DIRECTORY}/${BINUTILS_SOURCE_FOLDER_NAME}"
  GCC_SOURCE_FILE_NAME="$(basename "${GCC_SOURCE_URL}")"
  GCC_SOURCE_FOLDER_NAME="$(basename "${GCC_SOURCE_FILE_NAME}" .tar.gz)"
  GCC_SOURCE_FILE="${SOURCE_DIRECTORY}/${GCC_SOURCE_FILE_NAME}"
  GCC_SOURCE_DIRECTORY="${SOURCE_DIRECTORY}/${GCC_SOURCE_FOLDER_NAME}"

  # make source directory
  mkdir -p "${SOURCE_DIRECTORY}"

  # download source
  if [ ! -e "${BINUTILS_SOURCE_FILE}" ]; then
    echo "Download: ${BINUTILS_SOURCE_URL} -> ${BINUTILS_SOURCE_FILE}"
    curl --silent -o "${BINUTILS_SOURCE_FILE}" "${BINUTILS_SOURCE_URL}"
  fi
  if [ ! -e "${GCC_SOURCE_FILE}" ]; then
    echo "Download: ${GCC_SOURCE_URL} -> ${GCC_SOURCE_FILE}"
    curl --silent -o "${GCC_SOURCE_FILE}" "${GCC_SOURCE_URL}"
  fi

  # extract source
  if [ ! -d "${BINUTILS_SOURCE_DIRECTORY}" ]; then
    echo "Extract: ${BINUTILS_SOURCE_FILE} -> ${BINUTILS_SOURCE_DIRECTORY}"
    mkdir -p "${BINUTILS_SOURCE_DIRECTORY}"
    tar xzf "${BINUTILS_SOURCE_FILE}" --strip-components=1 -C "${BINUTILS_SOURCE_DIRECTORY}"
  fi
  if [ ! -d "${GCC_SOURCE_DIRECTORY}" ]; then
    echo "Extract: ${GCC_SOURCE_FILE} -> ${GCC_SOURCE_DIRECTORY}"
    mkdir -p "${GCC_SOURCE_DIRECTORY}"
    tar xzf "${GCC_SOURCE_FILE}" --strip-components=1 -C "${GCC_SOURCE_DIRECTORY}"
  fi

  ## build
  BINUTILS_BUILD_DIRECTORY="${BUILD_DIRECTORY}/binutils"
  GCC_BUILD_DIRECTORY="${BUILD_DIRECTORY}/gcc"
  MAKE="make -j${NUM_CPUS}"

  mkdir -p "${BINUTILS_BUILD_DIRECTORY}"
  cd "${BINUTILS_BUILD_DIRECTORY}"
  echo "Configuring binutils"
  "${BINUTILS_SOURCE_DIRECTORY}"/configure \
    --target="${TARGET}" \
    --prefix="${INSTALL_DIRECTORY}" \
    --with-sysroot \
    --disable-nls \
    --disable-werror \
    > configure.log 2>&1
  echo "Building binutils"
  {
    ${MAKE}
    ${MAKE} install
  } > make.log 2>&1
  cd "${PWD}"

  TARGET_AS="${TARGET}-as"
  echo "Ensuring ${TARGET_AS} is on PATH"
  PATH="$(path):${PATH}"
  command -v "${TARGET_AS}" > /dev/null 2>&1 || { echo "Unable to find ${TARGET_AS} on PATH"; exit 1; }

  mkdir -p "${GCC_BUILD_DIRECTORY}"
  cd "${GCC_BUILD_DIRECTORY}"
  echo "Configuring gcc"
  "${GCC_SOURCE_DIRECTORY}"/configure \
    --target="${TARGET}" \
    --prefix="${INSTALL_DIRECTORY}" \
    --disable-nls \
    --enable-languages=c,c++ \
    --without-headers \
    > configure.log 2>&1
  echo "Building gcc"
  {
    ${MAKE} all-gcc
    ${MAKE} all-target-libgcc
    ${MAKE} install-gcc
    ${MAKE} install-target-libgcc
  } > make.log 2>&1
  cd "${PWD}"

}

clean() {
  rm -rf "${SOURCE_DIRECTORY}"
  rm -rf "${BUILD_DIRECTORY}"
  rm -rf "${INSTALL_DIRECTORY}"
}

main() {
  ACTION="$1"
  if [ "${ACTION}" = "activate" ]; then
    activate
  elif [ "${ACTION}" = "build" ]; then
    build
  elif [ "${ACTION}" = "clean" ]; then
    clean
  elif [ "${ACTION}" = "path" ]; then
    path
  elif [ "${ACTION}" = "target" ]; then
    target
  else
    echo "Unrecognized action: ${ACTION}"
    exit 1
  fi

}

main "$@"
