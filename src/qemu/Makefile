CURRENT_DIRECTORY := $(abspath $(shell pwd))
ISO_SOURCE_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../iso)
ISO_INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/iso)

BUILD_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../build/qemu)
INSTALL_DIRECTORY := $(abspath $(CURRENT_DIRECTORY)/../../install/qemu)
SOURCE_DIRECTORY := $(CURRENT_DIRECTORY)

.PHONY: _default clean all run gdb $(ISO_INSTALL_DIRECTORY)/os.iso
_default: all

clean:
	@rm -rf $(BUILD_DIRECTORY)
	@rm -rf $(INSTALL_DIRECTORY)

$(ISO_INSTALL_DIRECTORY)/os.iso:
	${MAKE} -C $(ISO_SOURCE_DIRECTORY) $(ISO_INSTALL_DIRECTORY)/os.iso

run: $(ISO_INSTALL_DIRECTORY)/os.iso
	@qemu-system-i386 -cdrom $(ISO_INSTALL_DIRECTORY)/os.iso

gdb: $(ISO_INSTALL_DIRECTORY)/os.iso
	@qemu-system-i386 -cdrom $(ISO_INSTALL_DIRECTORY)/os.iso -S -gdb tcp::9000

all: run
