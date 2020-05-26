# OS

## Development

### Building a Toolchain

If you've built your own cross-compiler, you'll need to create
 a CMake toolchain file like [this one](./toolchain/toolchain.cmake).

Alternatively, you can try your luck with this [helper script](./toolchain/main.sh).
 
### Working with CMake

With your toolchain file in hand, building the project is a matter of:

```shell script
cd (build_directory)
cmake (path to source root) -DCMAKE_TOOLCHAIN_FILE=(path to toolchain file) -DCMAKE_INSTALL_PREFIX=(path to install directory)
# sync headers changes with sysroot
make copy-headers
# build
make all
# install
make install
```

With a built sysroot, you can generate an `iso` that you can use with `qemu`:

```shell script
make iso
qemu-system-i386 -cdrom (install path)/os.iso
```

### Working within CLion

Here are a few configuration pointers that will help you get
 on your feet a lil' quicker:

* Build, Execution and Deployment -> Toolchains
  * Ensure this points to your cross-compiler.
  * Make sure your cross-compiler is the default (move to top of list)
* Build, Execution and Deployment -> CMake
  * Ensure each profile uses the cross-compiler toolchain
  * CMake Options:
    * -DCMAKE_TOOLCHAIN_FILE=(path to .cmake toolchain file) 
    * -DCMAKE_INSTALL_PREFIX=(absolute installation path)
  * Generation path: (build directory)
* Run Configurations
  * Templates
    * 'Delete run configurations for missing CMake targets automatically': False
      * When CLion can't detect the run targets for CMake (say, bad toolchain) - it deletes
        all run configurations.  Including ones other run configurations depend upon. 
  * For any CMake Application target that needs an executable, use `/usr/bin/true`.  
    * Do this for `copy-headers` and `iso`
  * Create a CMake Application:
    * Name: "Build and install all targets"
    * Targets: All
    * Executable: `/usr/bin/true`
    * Before launch action:
      * Build
      * Install
  * Create a GDB Remote Debug Run Configuration:
    * Name: "QEMU Debug Attach"
    * Target Remote Args: localhost:1234
    * Symbols file: (install path)/sysroot/boot/kernel-bin
    * Before launch actions:
      * Run CMake Application `copy-headers`
      * Run CMake Application `build-and-install-all`
      * Run CMake Application `iso`
      * Run Shell Script `./scripts/qemu-debug.sh`
