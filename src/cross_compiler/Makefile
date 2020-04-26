CURRENT_DIRECTORY := $(abspath $(shell pwd))
BUILD_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../../build/cross_compiler)
INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../../install/cross_compiler)

TARGET := "i686-elf"
NCPU := 8

.PHONY: _default binutils gcc cross_compiler clean
_default: all

all: binutils gcc

$(BUILD_DIRECTORY):
	@mkdir -p $(BUILD_DIRECTORY)

$(BUILD_DIRECTORY)/binutils:
	@mkdir -p $(BUILD_DIRECTORY)/binutils

$(BUILD_DIRECTORY)/gcc:
	@mkdir -p $(BUILD_DIRECTORY)/gcc

$(INSTALL_DIRECTORY):
	@mkdir -p $(INSTALL_DIRECTORY)

clean:
	@rm -rf $(BUILD_DIRECTORY)
	@rm -rf $(INSTALL_DIRECTORY)

binutils: $(BUILD_DIRECTORY)/binutils
	cd $(BUILD_DIRECTORY)/binutils && \
	    $(CURRENT_DIRECTORY)binutils/configure --target=$(TARGET) --prefix=$(INSTALL_DIRECTORY) --with-sysroot --disable-nls --disable-werror && \
        ${MAKE} -j$(NCPU) && \
        ${MAKE} install


gcc: PATH := $(INSTALL_DIRECTORY)/bin:$(PATH)
gcc: binutils $(BUILD_DIRECTORY)/gcc
	@$(TARGET)-as --version || { echo "$(TARGET)-as not on path"; exit 1; }
	cd $(BUILD_DIRECTORY) && \
		$(CURRENT_DIRECTORY)/gcc/configure --target=${TARGET} --prefix=${INSTALL_DIRECTORY} --disable-nls --enable-languages=c,c++ --without-headers && \
		${MAKE} all-gcc all-target-libgcc -j${NCPU} && \
		${MAKE} install-gcc install-target-libgcc
