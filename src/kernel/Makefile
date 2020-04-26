CURRENT_DIRECTORY := $(abspath $(shell pwd))
CROSS_COMPILER := $(abspath $(CURRENT_DIRECTORY)/../../install/cross_compiler)

BUILD_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../build/kernel)
INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/kernel)
SOURCE_DIRECTORY := $(CURRENT_DIRECTORY)
TARGET := "i686-elf"
ARCH := "i386"
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

$(BUILD_DIRECTORY)/boot.o: $(BUILD_DIRECTORY)
	@$(TARGET)-as $(SOURCE_DIRECTORY)/$(ARCH)/boot.s -o $(BUILD_DIRECTORY)/boot.o

$(BUILD_DIRECTORY)/kernel.o: $(BUILD_DIRECTORY)
	@$(TARGET)-g++ -c $(SOURCE_DIRECTORY)/$(ARCH)/kernel.cpp -o $(BUILD_DIRECTORY)/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

$(BUILD_DIRECTORY)/kernel.bin: $(BUILD_DIRECTORY)/kernel.o $(BUILD_DIRECTORY)/boot.o
	@$(TARGET)-gcc -T  $(SOURCE_DIRECTORY)/$(ARCH)/linker.ld -o $(BUILD_DIRECTORY)/kernel.bin -ffreestanding -O2 -nostdlib $(BUILD_DIRECTORY)/boot.o $(BUILD_DIRECTORY)/kernel.o -lgcc

$(INSTALL_DIRECTORY)/kernel.bin: $(INSTALL_DIRECTORY) $(BUILD_DIRECTORY)/kernel.bin
	@cp -R $(BUILD_DIRECTORY)/kernel.bin $(INSTALL_DIRECTORY)/kernel.bin

all: $(INSTALL_DIRECTORY)/kernel.bin
