# Cross-Compiler

Generally, just follow the instructions [here](https://wiki.osdev.org/GCC_Cross-Compiler).

## Dependencies

### Ubuntu 20.04

```shell script
sudo apt install -y build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev
```

## Source

Clone the source repositories:

```shell script
git clone git://sourceware.org/git/binutils-gdb.git binutils
git clone git://gcc.gnu.org/git/gcc.git gcc
```

Find your host machine's `gcc` version by running the following commands:

```shell script
gcc -v
```

Find a version of `binutils` released at a time less than or equal to the `gcc` version on your host.

Check out the corresponding release tags to the versions you've found.

For `binutils`, the release tag format looks like `binutils-<major>_<minor>`.  If your host `binutils` version is 
 `2.34`, you'll want to check out `binutils-2_34`.  
 
For `gcc`, the release tag format looks like `releases/gcc-<major>.<minor>.<patch>`.  If your host `gcc` version is
 `9.3.0`, you'll want to check out `releases/gcc-9.3.0`.

## Build

Define your environment in your current terminal session:

```shell script
export BUILD_DIRECTORY="<directory>"
export INSTALL_DIRECTORY="<directory>"
export SOURCE_BINUTILS_DIRECTORY="<directory>"
export SOURCE_GCC_DIRECTORY="<directory>"
export TARGET="i686-elf"

export PREFIX="$INSTALL_DIRECTORY"
export PATH="$PREFIX/bin:$PATH"
```

Build `binutils`.

```shell script
mkdir -p "$BUILD_DIRECTORY/binutils"
cd "$BUILD_DIRECTORY/binutils"
"$SOURCE_BINUTILS_DIRECTORY/configure" --target="$TARGET" --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make 
make install
```

Build `gcc`.

```shell script
mkdir -p "$BUILD_DIRECTORY/gcc"
cd "$BUILD_DIRECTORY/gcc"
"$SOURCE_GCC_DIRECTORY/configure" --target="$TARGET" --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
male all-gcc 
make all-target-libgcc 
make install-gcc 
make install-target-libgcc
```

## Helper Script

A helper script is provided, but is not supported.

Modify `config.sh` to reflect your particular environment, and run `./build.sh` accordingly.  There's a check that
 will block you from running the script blindly.  You'll have to read `build.sh` to find and satisfy the check.

