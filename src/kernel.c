#include "addresses.h"
#include "debug.h"
#include "gdt.h"
#include "interrupt.h"
#include "keyboard.h"
#include "memory.h"
#include "splash.h"
#include "string.h"
#include "terminal.h"

/* Check if the compiler thinks you are targeting the wrong OS */
#if defined(__linux__)
#error "You are not using a cross-compiler; you will run into trouble!"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with an ix86-elf compiler"
#endif

void kernel_main(void) {
    init_gdt();
    memory_init();
    init_interrupts();

    terminal_initialize();
	splash_draw_luminos();
    terminal_writestring("\n");
    splash_draw_lamp();

    uint32_t *debug_ptr = (uint32_t *) RAM_START - 4;
    uint32_t current = *debug_ptr;
    while (1) {
        if (current != *debug_ptr) {
            current = *debug_ptr;
            printf("IRQ1 interrupt count: %d\n", current);
        }
    }
}
