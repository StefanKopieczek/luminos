OBJS:=build/boot.o build/kernel.o build/splash.o build/terminal.o build/util.o

CRTI_OBJ=build/crti.o
CRTBEGIN_OBJ:=$(shell toolchain/bin/i686-elf-g++ -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell toolchain/bin/i686-elf-g++ -print-file-name=crtend.o)
CRTN_OBJ=build/crtn.o
OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

define assemble
	toolchain/bin/i686-elf-as src/$(1).s -o build/$(1).o
endef

define compile
	toolchain/bin/i686-elf-g++ -c src/$(1).cpp -o build/$(1).o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti
endef

.PHONY: clean
clean:
	rm -rf build

.PHONY: build-dir
build-dir:
	mkdir -p build

build/boot.o: build-dir
	$(call assemble,boot)

build/crti.o: build-dir
	$(call assemble,crti)

build/crtn.o: build-dir
	$(call assemble,crtn)

build/kernel.o: build-dir
	$(call compile,kernel)

build/splash.o: build-dir
	$(call compile,splash)

build/terminal.o: build-dir
	$(call compile,terminal)

build/util.o: build-dir
	$(call compile,util)

.PHONY: link-kernel
link-kernel: $(OBJ_LINK_LIST)
	toolchain/bin/i686-elf-g++ -T src/linker.ld -o build/luminos.bin -ffreestanding -O2 -nostdlib $(OBJ_LINK_LIST) -lgcc

.PHONY: confirm-multiboot
confirm-multiboot:
	grub-file --is-x86-multiboot build/luminos.bin

build/luminos.bin: link-kernel confirm-multiboot

build/luminos.iso: build/luminos.bin
	mkdir -p build/isodir/boot/grub
	cp build/luminos.bin build/isodir/boot
	cp src/grub.cfg build/isodir/boot/grub
	grub-mkrescue -o build/luminos.iso build/isodir

.PHONY: qemu
qemu: build/luminos.iso
	qemu-system-i386 -cdrom build/luminos.iso
