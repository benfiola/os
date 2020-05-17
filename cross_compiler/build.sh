#!/bin/sh -e

error() {
  MESSAGE="$1"
  echo "$MESSAGE"
  exit 1
}

clone_binutils() {
  git clone "$SOURCE_BINUTILS_URL" "$SOURCE_GCC_DIRECTORY"
}

checkout_binutils() {
  cd "$SOURCE_BINUTILS_DIRECTORY"
  git checkout "$SOURCE_BINUTILS_TAG"
  cd "$CWD"
}

clone_gcc() {
  git clone "$SOURCE_GCC_URL" "$SOURCE_GCC_DIRECTORY"
}

checkout_gcc() {
  cd "$SOURCE_GCC_DIRECTORY"
  git checkout "$SOURCE_GCC_TAG"
  cd "$CWD"
}

pre_build_check() {
  if [ ! -e "$(pwd)/.agree" ]; then
    # This script is meant to serve as an example by which others can automate building their
    # cross-compiler.  While this script worked under the environment in which it was developed,
    # it might not work for your environment and you'll need to modify this script to suit your needs
    # and your particular building scenarios.
    error "Pre-build file not found"
  fi
}

build_binutils() {
  mkdir -p "$BUILD_DIRECTORY/binutils"
  cd "$BUILD_DIRECTORY/binutils"
  "$SOURCE_BINUTILS_DIRECTORY/configure" --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
  make -j "$NCPU"
  make -j "$NCPU" install
  cd "$CWD"
}

check_binutils() {
  command -v "$TARGET-as" || error "$TARGET-as is not on the PATH"
}

build_gcc() {
  mkdir -p "$BUILD_DIRECTORY/gcc"
  cd "$BUILD_DIRECTORY/gcc"
  "$SOURCE_GCC_DIRECTORY/configure" --target="$TARGET" --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
  make -j "$NCPU" all-gcc
  make -j "$NCPU" all-target-libgcc
  make -j "$NCPU" install-gcc
  make -j "$NCPU" install-target-libgcc
  cd "$CWD"
}

main() {
  . ./config.sh

  echo "Build: $BUILD_DIRECTORY"
  echo "Install: $INSTALL_DIRECTORY"
  echo "Source (binutils): $SOURCE_BINUTILS_DIRECTORY"
  echo "Source (gcc): $SOURCE_GCC_DIRECTORY"

  CWD="$(pwd)"
  export CWD
  export PREFIX=$INSTALL_DIRECTORY
  export PATH="$PREFIX/bin:$PATH"

  echo "Working directory: $CWD"
  echo "Prefix: $PREFIX"
  echo "Path: $PATH"

  echo "Pre-build check"
  pre_build_check

  if [ ! -d "$SOURCE_BINUTILS_DIRECTORY" ]; then
    echo "Cloning binutls"
    clone_binutils
  fi
  echo "Checking out binutils tag"
  checkout_binutils

  if [ ! -d "$SOURCE_GCC_DIRECTORY" ]; then
    echo "Cloning gcc"
    clone_gcc
  fi
  echo "Checking out gcc tag"
  checkout_gcc

  echo "Building binutils"
  build_binutils

  echo "Post-binutils build check"
  check_binutils

  echo "Building gcc"
  build_gcc

  echo "Cross-compiler built to: $INSTALL_DIRECTORY/bin"
}


main