/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0              /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1              /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO   /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002        /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS)  /* checksum of above, to prove we are multiboot */

/*
Declare a multiboot header that marks the program as a kernel.
These are magic values that are documented in the multiboot standard.
The bootloader will search for this signature in the first 8 KiB of the
kernel file, aligned at a 32-bit boundary.
The signature is in its own section so the header can be forced to be
within the first 8 KiB of the kernel file.
*/
.section .multiboot.data
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/*
The multiboot standard does not define the value of the stack pointer
register (esp), and it is up to the kernel to provide a stack.
This allocates room for a small stack by creating a symbol at the bottom
of it, then allocating 16384 bytes for it, and finally creating a symbol
at the top. The stack grows downwards on x86. The stack is in its own
section so it can be marked 'nobits', which means the kernel file is
smaller because it does not contain an uninitialized stack.
The stack on x86 must be 16-byte aligned according to the System V ABI
standard, and de-facto extensions.
The compiler will assume the stack is properly aligned, and failure to
align the stack will result in undefined behaviour.
*/
.section .bootstrap_stack, "aw", @nobits
    .align 16
stack_bottom:
    .skip 16384  # 16 KiB
stack_top:

/* Preallocate pages used for paging. */
.section .bss, "aw", @nobits
    .align 4096
boot_page_directory:
    .skip 4096
boot_page_table1:
    .skip 4096

/* The linker script specifies _start as the entry point to the kernel,
and the bootloader will jump to this position once the kernel has been
loaded. It doesn't make sense to return from this function, as the
bootloader is gone.
*/
.section .multiboot.text
.global _start
.type _start, @function
_start:
    movl $(boot_page_table1 - 0xC0000000), %edi
    movl $0, %esi
    movl $1023, %ecx
1:
    cmpl $_kernel_start, %esi
    jl 2f
    cmpl $(_kernel_end - 0xC0000000), %esi
    jge 3f
    movl %esi, %edx
    orl $0x003, %edx
    movl %edx, (%edi)

2:
    addl $4096, %esi
    addl $4, %edi
    loop 1b

3:
    movl $(0x000B8000 | 0x003), boot_page_table1 - 0xC0000000 + 1023 * 4
    movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 0
	movl $(boot_page_table1 - 0xC0000000 + 0x003), boot_page_directory - 0xC0000000 + 768 * 4
    movl $(boot_page_directory - 0xC0000000), %ecx
	movl %ecx, %cr3
    movl %cr0, %ecx
	orl $0x80010000, %ecx
	movl %ecx, %cr0
    lea 4f, %ecx
	jmp *%ecx

.section .text

4:
    movl $0, boot_page_directory + 0
    movl %cr3, %ecx
    movl %ecx, %cr3
    mov $stack_top, %esp
    call _init
    call kernel_main
    call _fini

    /*
    If the system has nothing more to do, put the computer into an infinite
    loop. To do that:
    1) Disable interrupts with 'cli' (clear interrupt enable in eflags).
       They are already disabled by the bootloader, so this is not needed.
       Mind that you might later enable interrupts, and return from
       kernel_main (though this is sort of nonsensical to do).
    2) Wait for the next interrupt to arrive with 'hlt' (halt instruction).
       Since interrupts are disabled, this will lock up the computer.
    3) Jump to the 'hlt' instruction if it ever wakes up due to a
       non-maskable interrupt occuring, or due to system management mode.
    */
       cli
1:     hlt
       jmp 1b

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
.size _start, . - _start
*/
