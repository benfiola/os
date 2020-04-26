CURRENT_DIRECTORY := $(abspath $(shell pwd))
CROSS_COMPILER := $(abspath $(CURRENT_DIRECTORY)/../../install/cross_compiler)

BUILD_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../build/libc)
INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/libc)
SOURCE_DIRECTORY := $(CURRENT_DIRECTORY)
TARGET := "i686-elf"

export PATH := $(CROSS_COMPILER)/bin:$(PATH)

.PHONY: _default clean all
_default: all

clean:
	@rm -rf $(BUILD_DIRECTORY)
	@rm -rf $(INSTALL_DIRECTORY)

$(BUILD_DIRECTORY):
	@mkdir -p $(BUILD_DIRECTORY)

$(INSTALL_DIRECTORY):
	@mkdir -p $(INSTALL_DIRECTORY)

all:
