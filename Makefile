clean:
	rm -rf build

build-dir:
	mkdir -p build

assemble-bootfile: build-dir
	toolchain/bin/i686-elf-as src/boot.s -o build/boot.o

compile-kernel: build-dir
	toolchain/bin/i686-elf-gcc -c src/kernel.c -o build/kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra

.link-kernel: compile-kernel
	toolchain/bin/i686-elf-gcc -T src/linker.ld -o build/os.bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o -lgcc

confirm-multiboot:
	grub-file --is-x86-multiboot build/os.bin

link-kernel: assemble-bootfile compile-kernel .link-kernel confirm-multiboot

build-iso: link-kernel
	mkdir -p build/isodir/boot/grub
	cp build/os.bin build/isodir/boot
	cp src/grub.cfg build/isodir/boot/grub
	grub-mkrescue -o build/os.iso build/isodir

qemu: build-iso
	qemu-system-i386 -cdrom build/os.iso
