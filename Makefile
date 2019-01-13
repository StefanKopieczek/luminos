osname = luminos

clean:
	rm -rf build

build-dir:
	mkdir -p build

boot.o: build-dir
	toolchain/bin/i686-elf-as src/boot.s -o build/boot.o

kernel.o: build-dir
	toolchain/bin/i686-elf-g++ -c src/kernel.cpp -o build/kernel.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

terminal.o: build-dir
	toolchain/bin/i686-elf-g++ -c src/terminal.cpp -o build/terminal.o -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti

.link-kernel: boot.o kernel.o terminal.o
	toolchain/bin/i686-elf-g++ -T src/linker.ld -o build/$(osname).bin -ffreestanding -O2 -nostdlib build/boot.o build/kernel.o build/terminal.o -lgcc

confirm-multiboot:
	grub-file --is-x86-multiboot build/$(osname).bin

link-kernel: .link-kernel confirm-multiboot

build-iso: link-kernel
	mkdir -p build/isodir/boot/grub
	cp build/$(osname).bin build/isodir/boot
	cp src/grub.cfg build/isodir/boot/grub
	grub-mkrescue -o build/$(osname).iso build/isodir

qemu: build-iso
	qemu-system-i386 -cdrom build/$(osname).iso
