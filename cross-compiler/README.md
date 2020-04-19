# Cross-compiler

REFERENCE: [OSDev Wiki](https://wiki.osdev.org/GCC_Cross-Compiler)

Building a cross compiler is a necessary pre-requisite to enable us to build code on our current development platform
 targeting the platform on which our OS is going to run.

To build this cross-compiler:

* Install
  * `cmake`
  * `gcc`
  * `g++`
  * `make`
  * `bison`
  * `flex`
  * `gmp`
  * `mpfr`
  * `mpc`
  * `texinfo`
  * `isl`
* Run `cmake .`
* Run `make`

The cross-compiler should be built into ./install.

This cross-compiler will be a functional dependency of any parent-level CMake targets.
