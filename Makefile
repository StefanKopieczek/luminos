SRC=src
BUILD=build

CC=toolchain/bin/i686-elf-gcc
CFLAGS:=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
AS=toolchain/bin/i686-elf-as

CRTI_OBJ=$(BUILD)/globalinit/crti.o
CRTBEGIN_OBJ:=$(shell toolchain/bin/i686-elf-gcc -print-file-name=crtbegin.o)
CRTEND_OBJ:=$(shell toolchain/bin/i686-elf-gcc -print-file-name=crtend.o)
CRTN_OBJ=$(BUILD)/globalinit/crtn.o

C_SRCS:=$(wildcard $(SRC)/*.c) $(wildcard $(SRC)/**/*.c)
S_SRCS:=$(wildcard $(SRC)/*.s) $(wildcard $(SRC)/**/*.s)

C_OBJS:=$(patsubst $(SRC)/%.c,$(BUILD)/%.o,$(C_SRCS))
S_OBJS_RAW:=$(patsubst $(SRC)/%.s,$(BUILD)/%.o,$(S_SRCS))

# When we define OBJ_LINK_LIST later we'll need to put CRTI_OBJ first and CRTN_OBJ last
# in the input list, so filter them out of the main set of objects to avoid duplicating
# them.
S_OBJS:=$(filter-out $(CRTI_OBJ) $(CRTN_OBJ), $(S_OBJS_RAW))

OBJS:=$(C_OBJS) $(S_OBJS)
OBJ_LINK_LIST:=$(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: clean
clean:
	rm -rf $(BUILD)

$(BUILD)/%.o: $(SRC)/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD)/%.o: $(SRC)/%.s
	@mkdir -p $(@D)
	$(AS) -o $@ $<

$(BUILD)/%.o: $(SRC)/**/%.c
	@mkdir -p $(@D)
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD)/%.o: $(SRC)/**/%.s
	@mkdir -p $(@D)
	$(AS) -o $@ $<

.PHONY: link-kernel
link-kernel: $(OBJ_LINK_LIST)
	@mkdir -p $(BUILD)
	toolchain/bin/i686-elf-gcc -T $(SRC)/linker.ld -o $(BUILD)/luminos.bin -ffreestanding -O2 -nostdlib $(OBJ_LINK_LIST) -lgcc

.PHONY: confirm-multiboot
confirm-multiboot:
	@mkdir -p $(BUILD)
	grub-file --is-x86-multiboot $(BUILD)/luminos.bin

$(BUILD)/luminos.bin: link-kernel confirm-multiboot

$(BUILD)/luminos.iso: $(BUILD)/luminos.bin
	@mkdir -p $(BUILD)/isodir/boot/grub
	cp $(BUILD)/luminos.bin $(BUILD)/isodir/boot
	cp $(SRC)/boot/grub.cfg $(BUILD)/isodir/boot/grub
	grub-mkrescue -o $(BUILD)/luminos.iso $(BUILD)/isodir

.PHONY: iso
iso: $(BUILD)/luminos.iso

.PHONY: qemu
qemu: $(BUILD)/luminos.iso
	qemu-system-i386 -cdrom $(BUILD)/luminos.iso -d cpu_reset,int -D qemu.log

.PHONY: bochs
bochs: $(BUILD)/luminos.iso
	bochs
