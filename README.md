# OS

## Cross-compiler

### Dependencies

* g++
* gcc
* make
* bison
* flex
* libgmp3-dev
* libmpfr-dev
* libmpc-dev
* texinfo
* libisl-dev

### Building the cross-compiler

```
make cross_compiler/all
```

## Kernel

### Building the kernel

```
make kernel/all
```

## ISO

### Dependencies

* xorriso
* grub

### Building an ISO

```
make iso/all
```

## QEMU

### Run from ISO

```
qemu-system-x86_64 -cdrom install/iso/os.iso
```

### Run from kernel binary

```
qemu-system-x86_64 -kernel install/kernel/os.bin
```
