CURRENT_DIRECTORY := $(abspath $(shell pwd))

.PHONY: iso/all iso/clean kernel/all kernel/clean cross_compiler/all cross_compiler/clean libc/all libc/clean

iso/all:
	${MAKE} -C src/iso all

iso/clean:
	${MAKE} -C src/iso clean

kernel/all:
	${MAKE} -C src/kernel all

kernel/clean:
	${MAKE} -C src/kernel clean

cross_compiler/all:
	${MAKE} -C src/cross_compiler all

cross_compiler/clean:
	${MAKE} -C src/cross_compiler clean

libc/all:
	${MAKE} -C src/libc all

libc/clean:
	${MAKE} -C src/libc clean
