CURRENT_DIRECTORY := $(abspath $(shell pwd))
BUILD_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../build/cross_compiler)
INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/cross_compiler)

TARGET := i686-elf
NCPU := 8


.PHONY: _default binutils gcc cross_compiler clean
_default: all

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

binutils_deps =
binutils_deps += $(INSTALL_DIRECTORY)/bin/$(TARGET)-as
binutils_deps += $(INSTALL_DIRECTORY)/bin/$(TARGET)-ld
$(binutils_deps): | $(BUILD_DIRECTORY)/binutils $(INSTALL_DIRECTORY)
	cd $(BUILD_DIRECTORY)/binutils && \
	    $(CURRENT_DIRECTORY)/binutils/configure --target=$(TARGET) --prefix=$(INSTALL_DIRECTORY) --with-sysroot --disable-nls --disable-werror && \
        ${MAKE} -j$(NCPU) && \
        ${MAKE} install

gcc_deps =
gcc_deps += $(INSTALL_DIRECTORY)/bin/$(TARGET)-g++
gcc_deps += $(INSTALL_DIRECTORY)/bin/$(TARGET)-gcc
$(gcc_deps): PATH := $(INSTALL_DIRECTORY)/bin:$(PATH)
$(gcc_deps)+: $(binutils_deps) | $(BUILD_DIRECTORY)/gcc $(INSTALL_DIRECTORY)
	@$(TARGET)-as --version || { echo "$(TARGET)-as not on path"; exit 1; }
	cd $(BUILD_DIRECTORY)/gcc && \
		$(CURRENT_DIRECTORY)/gcc/configure --target=${TARGET} --prefix=${INSTALL_DIRECTORY} --disable-nls --enable-languages=c,c++ --without-headers && \
		${MAKE} all-gcc all-target-libgcc -j${NCPU} && \
		${MAKE} install-gcc install-target-libgcc

binutils: $(binutils_deps)
gcc: $(gcc_deps)

all: binutils gcc
