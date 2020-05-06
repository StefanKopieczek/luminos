#include <stddef.h>
#include <stdint.h>

#include "public.h"
#include "../addresses/public.h"
#include "../strings/public.h"

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
    return fg | bg << 4;
}

static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
    return (uint16_t) uc | (uint16_t) color << 8;
}

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

void terminal_initialize() {
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) VGA_BUFFER;
    for (size_t y = 0; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_scroll() {
    for (size_t y = 1; y < VGA_HEIGHT; y++) {
        for (size_t x = 0; x < VGA_WIDTH; x++) {
            const size_t from_idx = y * VGA_WIDTH + x;
            const size_t to_idx = (y - 1) * VGA_WIDTH + x;
            terminal_buffer[to_idx] = terminal_buffer[from_idx];
        }
    }

    for (size_t x = 0; x < VGA_WIDTH; x++) {
        const size_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
}

void terminal_setcolor(uint8_t color) {
    terminal_color = color;
}

void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_newline() {
    terminal_row++;
    terminal_column = 0;
    if (terminal_row >= VGA_HEIGHT) {
        terminal_scroll();
        terminal_row--;
    }
}

void terminal_put_printable_char(char c) {
    terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH) {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT) {
            terminal_row = 0;
        }
    }
}

void terminal_putchar(char c) {
    if (c == '\n') {
        terminal_newline();
    } else if (c == '\t') {
        for (int i = 0; i < 4; i++) {
            terminal_putchar(' ');
        }
    } else {
        terminal_put_printable_char(c);
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i = 0; i < size; i++) {
        terminal_putchar(data[i]);
    }
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}

void printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    char buf[10000]; // TODO
    vsprintf(buf, format, args);
    va_end(args);
    terminal_writestring(buf);
}
