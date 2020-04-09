#include "keyboard.h"
#include "memory.h"
#include <stdint.h>

static char scanCodes[256];

void init_keyboard() {
    memset(scanCodes, 0, 256);
    scanCodes[0x1e] = 'a';
    scanCodes[0x30] = 'b';
    scanCodes[0x2e] = 'c';
    scanCodes[0x20] = 'd';
    scanCodes[0x12] = 'e';
    scanCodes[0x21] = 'f';
    scanCodes[0x22] = 'g';
    scanCodes[0x23] = 'h';
    scanCodes[0x17] = 'i';
    scanCodes[0x24] = 'j';
    scanCodes[0x25] = 'k';
    scanCodes[0x26] = 'l';
    scanCodes[0x32] = 'm';
    scanCodes[0x31] = 'n';
    scanCodes[0x18] = 'o';
    scanCodes[0x19] = 'p';
    scanCodes[0x10] = 'q';
    scanCodes[0x13] = 'r';
    scanCodes[0x1f] = 's';
    scanCodes[0x14] = 't';
    scanCodes[0x16] = 'u';
    scanCodes[0x2f] = 'v';
    scanCodes[0x11] = 'w';
    scanCodes[0x2d] = 'x';
    scanCodes[0x15] = 'y';
    scanCodes[0x2c] = 'z';
}



uint8_t read_port (uint16_t _port) {
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

char get_current_key() {
    return scanCodes[read_port(0x60)];
}

