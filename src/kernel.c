#include "gdt.h"
#include "addresses.h"
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
    terminal_initialize();
	splash_draw_luminos();
	terminal_writestring("\n");
    splash_draw_lamp();

    char buf0[200];
    sprintf(buf0, "1+2=%s\n", "3");
    terminal_writestring(buf0);
    char buf[200];
    sprintf(buf, "%s=%d\n", "2+2", 4);
    terminal_writestring(buf);

    init_keyboard();
    while (1) {
        keyboard_key key = wait_for_key();
        if (key_is_char(key)) {
            terminal_putchar(key_to_char(key));
        }
    }
}
