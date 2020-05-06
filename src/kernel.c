#include "addresses/public.h"
#include "debugging/public.h"
#include "gdt/public.h"
#include "interrupts/public.h"
#include "keyboard/public.h"
#include "memory/public.h"
#include "splash/public.h"
#include "strings/public.h"
#include "terminal/public.h"

/* Check if the compiler thinks you are targeting the wrong OS */
#if defined(__linux__)
#error "You are not using a cross-compiler; you will run into trouble!"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This tutorial needs to be compiled with an ix86-elf compiler"
#endif

void kernel_main(void) {
    uint32_t *debug_ptr = (uint32_t *) (RAM_START + 4);
    *debug_ptr = 0x0;
    uint32_t current = *debug_ptr;

    init_gdt();
    memory_init();
    init_interrupts();

    terminal_initialize();
	splash_draw_luminos();
    terminal_writestring("\n");
    splash_draw_lamp();
}
