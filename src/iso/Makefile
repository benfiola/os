CURRENT_DIRECTORY := $(abspath $(shell pwd))
KERNEL_SOURCE_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../kernel)
KERNEL_INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/kernel)

BUILD_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../build/iso)
INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/iso)
SOURCE_DIRECTORY := $(CURRENT_DIRECTORY)

.PHONY: _default clean all $(KERNEL_INSTALL_DIRECTORY)/kernel.bin
_default: all

clean:
	@rm -rf $(BUILD_DIRECTORY)
	@rm -rf $(INSTALL_DIRECTORY)

$(BUILD_DIRECTORY):
	@mkdir -p $(BUILD_DIRECTORY)

$(INSTALL_DIRECTORY):
	@mkdir -p $(INSTALL_DIRECTORY)

$(BUILD_DIRECTORY)/root: $(BUILD_DIRECTORY)
	@mkdir -p $(BUILD_DIRECTORY)/root

$(BUILD_DIRECTORY)/root/boot: $(BUILD_DIRECTORY)/root
	@mkdir -p $(BUILD_DIRECTORY)/root/boot

$(BUILD_DIRECTORY)/root/boot/grub: $(BUILD_DIRECTORY)/root/boot
	@mkdir -p $(BUILD_DIRECTORY)/root/boot/grub

$(KERNEL_INSTALL_DIRECTORY)/kernel.bin:
	${MAKE} -C $(KERNEL_SOURCE_DIRECTORY) $(KERNEL_INSTALL_DIRECTORY)/kernel.bin

$(BUILD_DIRECTORY)/root/boot/kernel.bin: $(BUILD_DIRECTORY)/root/boot $(KERNEL_INSTALL_DIRECTORY)/kernel.bin
	@cp -R $(KERNEL_INSTALL_DIRECTORY)/kernel.bin $(BUILD_DIRECTORY)/root/boot/kernel.bin

$(BUILD_DIRECTORY)/root/boot/grub/grub.cfg: $(BUILD_DIRECTORY)/root/boot/grub
	@cp -R $(CURRENT_DIRECTORY)/grub.cfg $(BUILD_DIRECTORY)/root/boot/grub/grub.cfg

$(BUILD_DIRECTORY)/os.iso: $(BUILD_DIRECTORY)/root/boot/grub/grub.cfg $(BUILD_DIRECTORY)/root/boot/kernel.bin
	@grub-mkrescue -o $(BUILD_DIRECTORY)/os.iso $(BUILD_DIRECTORY)/root

$(INSTALL_DIRECTORY)/os.iso: $(BUILD_DIRECTORY)/os.iso $(INSTALL_DIRECTORY)
	@cp -R $(BUILD_DIRECTORY)/os.iso $(INSTALL_DIRECTORY)/os.iso

all: $(INSTALL_DIRECTORY)/os.iso
