#include <stdint.h>

#include "public.h"
#include "../memory/public.h"
#include "../ports/public.h"
#include "../terminal/public.h"

static keyboard_event scanCodes[256];

void init_keyboard() {
    memset(scanCodes, 0, 256);
    scanCodes[0x01] = (keyboard_event) {KEY_ESCAPE, KEY_PRESSED};
    scanCodes[0x02] = (keyboard_event) {KEY_1, KEY_PRESSED};
    scanCodes[0x03] = (keyboard_event) {KEY_2, KEY_PRESSED};
    scanCodes[0x04] = (keyboard_event) {KEY_3, KEY_PRESSED};
    scanCodes[0x05] = (keyboard_event) {KEY_4, KEY_PRESSED};
    scanCodes[0x06] = (keyboard_event) {KEY_5, KEY_PRESSED};
    scanCodes[0x07] = (keyboard_event) {KEY_6, KEY_PRESSED};
    scanCodes[0x08] = (keyboard_event) {KEY_7, KEY_PRESSED};
    scanCodes[0x09] = (keyboard_event) {KEY_8, KEY_PRESSED};
    scanCodes[0x0a] = (keyboard_event) {KEY_9, KEY_PRESSED};
    scanCodes[0x0b] = (keyboard_event) {KEY_0, KEY_PRESSED};
    scanCodes[0x0c] = (keyboard_event) {KEY_MINUS, KEY_PRESSED};
    scanCodes[0x0d] = (keyboard_event) {KEY_EQUALS, KEY_PRESSED};
    scanCodes[0x0e] = (keyboard_event) {KEY_BACKSPACE, KEY_PRESSED};
    scanCodes[0x0f] = (keyboard_event) {KEY_TAB, KEY_PRESSED};
    scanCodes[0x10] = (keyboard_event) {KEY_Q, KEY_PRESSED};
    scanCodes[0x11] = (keyboard_event) {KEY_W, KEY_PRESSED};
    scanCodes[0x12] = (keyboard_event) {KEY_E, KEY_PRESSED};
    scanCodes[0x13] = (keyboard_event) {KEY_R, KEY_PRESSED};
    scanCodes[0x14] = (keyboard_event) {KEY_T, KEY_PRESSED};
    scanCodes[0x15] = (keyboard_event) {KEY_Y, KEY_PRESSED};
    scanCodes[0x16] = (keyboard_event) {KEY_U, KEY_PRESSED};
    scanCodes[0x17] = (keyboard_event) {KEY_I, KEY_PRESSED};
    scanCodes[0x18] = (keyboard_event) {KEY_O, KEY_PRESSED};
    scanCodes[0x19] = (keyboard_event) {KEY_P, KEY_PRESSED};
    scanCodes[0x1a] = (keyboard_event) {KEY_LEFT_SQUARE_BRACKET, KEY_PRESSED};
    scanCodes[0x1b] = (keyboard_event) {KEY_RIGHT_SQUARE_BRACKET, KEY_PRESSED};
    scanCodes[0x1c] = (keyboard_event) {KEY_ENTER, KEY_PRESSED};
    scanCodes[0x1d] = (keyboard_event) {KEY_LEFT_CONTROL, KEY_PRESSED};
    scanCodes[0x1e] = (keyboard_event) {KEY_A, KEY_PRESSED};
    scanCodes[0x1f] = (keyboard_event) {KEY_S, KEY_PRESSED};
    scanCodes[0x20] = (keyboard_event) {KEY_D, KEY_PRESSED};
    scanCodes[0x21] = (keyboard_event) {KEY_F, KEY_PRESSED};
    scanCodes[0x22] = (keyboard_event) {KEY_G, KEY_PRESSED};
    scanCodes[0x23] = (keyboard_event) {KEY_H, KEY_PRESSED};
    scanCodes[0x24] = (keyboard_event) {KEY_J, KEY_PRESSED};
    scanCodes[0x25] = (keyboard_event) {KEY_K, KEY_PRESSED};
    scanCodes[0x26] = (keyboard_event) {KEY_L, KEY_PRESSED};
    scanCodes[0x27] = (keyboard_event) {KEY_SEMICOLON, KEY_PRESSED};
    scanCodes[0x28] = (keyboard_event) {KEY_SINGLE_QUOTE, KEY_PRESSED};
    scanCodes[0x29] = (keyboard_event) {KEY_BACKTICK, KEY_PRESSED};
    scanCodes[0x2a] = (keyboard_event) {KEY_LEFT_SHIFT, KEY_PRESSED};
    scanCodes[0x2b] = (keyboard_event) {KEY_BACKSLASH, KEY_PRESSED};
    scanCodes[0x2c] = (keyboard_event) {KEY_Z, KEY_PRESSED};
    scanCodes[0x2d] = (keyboard_event) {KEY_X, KEY_PRESSED};
    scanCodes[0x2e] = (keyboard_event) {KEY_C, KEY_PRESSED};
    scanCodes[0x2f] = (keyboard_event) {KEY_V, KEY_PRESSED};
    scanCodes[0x30] = (keyboard_event) {KEY_B, KEY_PRESSED};
    scanCodes[0x31] = (keyboard_event) {KEY_N, KEY_PRESSED};
    scanCodes[0x32] = (keyboard_event) {KEY_M, KEY_PRESSED};
    scanCodes[0x33] = (keyboard_event) {KEY_COMMA, KEY_PRESSED};
    scanCodes[0x34] = (keyboard_event) {KEY_PERIOD, KEY_PRESSED};
    scanCodes[0x35] = (keyboard_event) {KEY_FORWARD_SLASH, KEY_PRESSED};
    scanCodes[0x36] = (keyboard_event) {KEY_RIGHT_SHIFT, KEY_PRESSED};
    scanCodes[0x37] = (keyboard_event) {KEY_KEYPAD_ASTERISK, KEY_PRESSED};
    scanCodes[0x38] = (keyboard_event) {KEY_LEFT_ALT, KEY_PRESSED};
    scanCodes[0x39] = (keyboard_event) {KEY_SPACEBAR, KEY_PRESSED};
    scanCodes[0x3a] = (keyboard_event) {KEY_CAPSLOCK, KEY_PRESSED};
    scanCodes[0x3b] = (keyboard_event) {KEY_F1, KEY_PRESSED};
    scanCodes[0x3c] = (keyboard_event) {KEY_F2, KEY_PRESSED};
    scanCodes[0x3d] = (keyboard_event) {KEY_F3, KEY_PRESSED};
    scanCodes[0x3e] = (keyboard_event) {KEY_F4, KEY_PRESSED};
    scanCodes[0x3f] = (keyboard_event) {KEY_F5, KEY_PRESSED};
    scanCodes[0x40] = (keyboard_event) {KEY_F6, KEY_PRESSED};
    scanCodes[0x41] = (keyboard_event) {KEY_F7, KEY_PRESSED};
    scanCodes[0x42] = (keyboard_event) {KEY_F8, KEY_PRESSED};
    scanCodes[0x43] = (keyboard_event) {KEY_F9, KEY_PRESSED};
    scanCodes[0x44] = (keyboard_event) {KEY_F10, KEY_PRESSED};
    scanCodes[0x45] = (keyboard_event) {KEY_NUMLOCK, KEY_PRESSED};
    scanCodes[0x46] = (keyboard_event) {KEY_SCROLL_LOCK, KEY_PRESSED};
    scanCodes[0x47] = (keyboard_event) {KEY_KEYPAD_7, KEY_PRESSED};
    scanCodes[0x48] = (keyboard_event) {KEY_KEYPAD_8, KEY_PRESSED};
    scanCodes[0x49] = (keyboard_event) {KEY_KEYPAD_9, KEY_PRESSED};
    scanCodes[0x4a] = (keyboard_event) {KEY_KEYPAD_MINUS, KEY_PRESSED};
    scanCodes[0x4b] = (keyboard_event) {KEY_KEYPAD_4, KEY_PRESSED};
    scanCodes[0x4c] = (keyboard_event) {KEY_KEYPAD_5, KEY_PRESSED};
    scanCodes[0x4d] = (keyboard_event) {KEY_KEYPAD_6, KEY_PRESSED};
    scanCodes[0x4e] = (keyboard_event) {KEY_KEYPAD_PLUS, KEY_PRESSED};
    scanCodes[0x4f] = (keyboard_event) {KEY_KEYPAD_1, KEY_PRESSED};
    scanCodes[0x50] = (keyboard_event) {KEY_KEYPAD_2, KEY_PRESSED};
    scanCodes[0x51] = (keyboard_event) {KEY_KEYPAD_3, KEY_PRESSED};
    scanCodes[0x52] = (keyboard_event) {KEY_KEYPAD_0, KEY_PRESSED};
    scanCodes[0x53] = (keyboard_event) {KEY_KEYPAD_PERIOD, KEY_PRESSED};
    scanCodes[0x57] = (keyboard_event) {KEY_F11, KEY_PRESSED};
    scanCodes[0x58] = (keyboard_event) {KEY_F12, KEY_PRESSED};
    scanCodes[0x81] = (keyboard_event) {KEY_ESCAPE, KEY_RELEASED};
    scanCodes[0x82] = (keyboard_event) {KEY_1, KEY_RELEASED};
    scanCodes[0x83] = (keyboard_event) {KEY_2, KEY_RELEASED};
    scanCodes[0x84] = (keyboard_event) {KEY_3, KEY_RELEASED};
    scanCodes[0x85] = (keyboard_event) {KEY_4, KEY_RELEASED};
    scanCodes[0x86] = (keyboard_event) {KEY_5, KEY_RELEASED};
    scanCodes[0x87] = (keyboard_event) {KEY_6, KEY_RELEASED};
    scanCodes[0x88] = (keyboard_event) {KEY_7, KEY_RELEASED};
    scanCodes[0x89] = (keyboard_event) {KEY_8, KEY_RELEASED};
    scanCodes[0x8a] = (keyboard_event) {KEY_9, KEY_RELEASED};
    scanCodes[0x8b] = (keyboard_event) {KEY_0, KEY_RELEASED};
    scanCodes[0x8c] = (keyboard_event) {KEY_MINUS, KEY_RELEASED};
    scanCodes[0x8d] = (keyboard_event) {KEY_EQUALS, KEY_RELEASED};
    scanCodes[0x8e] = (keyboard_event) {KEY_BACKSPACE, KEY_RELEASED};
    scanCodes[0x8f] = (keyboard_event) {KEY_TAB, KEY_RELEASED};
    scanCodes[0x90] = (keyboard_event) {KEY_Q, KEY_RELEASED};
    scanCodes[0x91] = (keyboard_event) {KEY_W, KEY_RELEASED};
    scanCodes[0x92] = (keyboard_event) {KEY_E, KEY_RELEASED};
    scanCodes[0x93] = (keyboard_event) {KEY_R, KEY_RELEASED};
    scanCodes[0x94] = (keyboard_event) {KEY_T, KEY_RELEASED};
    scanCodes[0x95] = (keyboard_event) {KEY_Y, KEY_RELEASED};
    scanCodes[0x96] = (keyboard_event) {KEY_U, KEY_RELEASED};
    scanCodes[0x97] = (keyboard_event) {KEY_I, KEY_RELEASED};
    scanCodes[0x98] = (keyboard_event) {KEY_O, KEY_RELEASED};
    scanCodes[0x99] = (keyboard_event) {KEY_P, KEY_RELEASED};
    scanCodes[0x9a] = (keyboard_event) {KEY_LEFT_SQUARE_BRACKET, KEY_RELEASED};
    scanCodes[0x9b] = (keyboard_event) {KEY_RIGHT_SQUARE_BRACKET, KEY_RELEASED};
    scanCodes[0x9c] = (keyboard_event) {KEY_ENTER, KEY_RELEASED};
    scanCodes[0x9d] = (keyboard_event) {KEY_LEFT_CONTROL, KEY_RELEASED};
    scanCodes[0x9e] = (keyboard_event) {KEY_A, KEY_RELEASED};
    scanCodes[0x9f] = (keyboard_event) {KEY_S, KEY_RELEASED};
    scanCodes[0xa0] = (keyboard_event) {KEY_D, KEY_RELEASED};
    scanCodes[0xa1] = (keyboard_event) {KEY_F, KEY_RELEASED};
    scanCodes[0xa2] = (keyboard_event) {KEY_G, KEY_RELEASED};
    scanCodes[0xa3] = (keyboard_event) {KEY_H, KEY_RELEASED};
    scanCodes[0xa4] = (keyboard_event) {KEY_J, KEY_RELEASED};
    scanCodes[0xa5] = (keyboard_event) {KEY_K, KEY_RELEASED};
    scanCodes[0xa6] = (keyboard_event) {KEY_L, KEY_RELEASED};
    scanCodes[0xa7] = (keyboard_event) {KEY_SEMICOLON, KEY_RELEASED};
    scanCodes[0xa8] = (keyboard_event) {KEY_SINGLE_QUOTE, KEY_RELEASED};
    scanCodes[0xa9] = (keyboard_event) {KEY_BACKTICK, KEY_RELEASED};
    scanCodes[0xaa] = (keyboard_event) {KEY_LEFT_SHIFT, KEY_RELEASED};
    scanCodes[0xab] = (keyboard_event) {KEY_BACKSLASH, KEY_RELEASED};
    scanCodes[0xac] = (keyboard_event) {KEY_Z, KEY_RELEASED};
    scanCodes[0xad] = (keyboard_event) {KEY_X, KEY_RELEASED};
    scanCodes[0xae] = (keyboard_event) {KEY_C, KEY_RELEASED};
    scanCodes[0xaf] = (keyboard_event) {KEY_V, KEY_RELEASED};
    scanCodes[0xb0] = (keyboard_event) {KEY_B, KEY_RELEASED};
    scanCodes[0xb1] = (keyboard_event) {KEY_N, KEY_RELEASED};
    scanCodes[0xb2] = (keyboard_event) {KEY_M, KEY_RELEASED};
    scanCodes[0xb3] = (keyboard_event) {KEY_COMMA, KEY_RELEASED};
    scanCodes[0xb4] = (keyboard_event) {KEY_PERIOD, KEY_RELEASED};
    scanCodes[0xb5] = (keyboard_event) {KEY_FORWARD_SLASH, KEY_RELEASED};
    scanCodes[0xb6] = (keyboard_event) {KEY_RIGHT_SHIFT, KEY_RELEASED};
    scanCodes[0xb7] = (keyboard_event) {KEY_KEYPAD_ASTERISK, KEY_RELEASED};
    scanCodes[0xb8] = (keyboard_event) {KEY_LEFT_ALT, KEY_RELEASED};
    scanCodes[0xb9] = (keyboard_event) {KEY_SPACEBAR, KEY_RELEASED};
    scanCodes[0xba] = (keyboard_event) {KEY_CAPSLOCK, KEY_RELEASED};
    scanCodes[0xbb] = (keyboard_event) {KEY_F1, KEY_RELEASED};
    scanCodes[0xbc] = (keyboard_event) {KEY_F2, KEY_RELEASED};
    scanCodes[0xbd] = (keyboard_event) {KEY_F3, KEY_RELEASED};
    scanCodes[0xbe] = (keyboard_event) {KEY_F4, KEY_RELEASED};
    scanCodes[0xbf] = (keyboard_event) {KEY_F5, KEY_RELEASED};
    scanCodes[0xc0] = (keyboard_event) {KEY_F6, KEY_RELEASED};
    scanCodes[0xc1] = (keyboard_event) {KEY_F7, KEY_RELEASED};
    scanCodes[0xc2] = (keyboard_event) {KEY_F8, KEY_RELEASED};
    scanCodes[0xc3] = (keyboard_event) {KEY_F9, KEY_RELEASED};
    scanCodes[0xc4] = (keyboard_event) {KEY_F10, KEY_RELEASED};
    scanCodes[0xc5] = (keyboard_event) {KEY_NUMLOCK, KEY_RELEASED};
    scanCodes[0xc6] = (keyboard_event) {KEY_SCROLL_LOCK, KEY_RELEASED};
    scanCodes[0xc7] = (keyboard_event) {KEY_KEYPAD_7, KEY_RELEASED};
    scanCodes[0xc8] = (keyboard_event) {KEY_KEYPAD_8, KEY_RELEASED};
    scanCodes[0xc9] = (keyboard_event) {KEY_KEYPAD_9, KEY_RELEASED};
    scanCodes[0xca] = (keyboard_event) {KEY_KEYPAD_MINUS, KEY_RELEASED};
    scanCodes[0xcb] = (keyboard_event) {KEY_KEYPAD_4, KEY_RELEASED};
    scanCodes[0xcc] = (keyboard_event) {KEY_KEYPAD_5, KEY_RELEASED};
    scanCodes[0xcd] = (keyboard_event) {KEY_KEYPAD_6, KEY_RELEASED};
    scanCodes[0xce] = (keyboard_event) {KEY_KEYPAD_PLUS, KEY_RELEASED};
    scanCodes[0xcf] = (keyboard_event) {KEY_KEYPAD_1, KEY_RELEASED};
    scanCodes[0xd0] = (keyboard_event) {KEY_KEYPAD_2, KEY_RELEASED};
    scanCodes[0xd1] = (keyboard_event) {KEY_KEYPAD_3, KEY_RELEASED};
    scanCodes[0xd2] = (keyboard_event) {KEY_KEYPAD_0, KEY_RELEASED};
    scanCodes[0xd3] = (keyboard_event) {KEY_KEYPAD_PERIOD, KEY_RELEASED};
    scanCodes[0xd7] = (keyboard_event) {KEY_F11, KEY_RELEASED};
    scanCodes[0xd8] = (keyboard_event) {KEY_F12, KEY_RELEASED};
}


keyboard_event get_last_event() {
    return scanCodes[port_read(0x60)];
}

keyboard_key wait_for_key() {
    keyboard_event current;
    keyboard_key trapped = NO_KEY;
    while (true) {
        current = get_last_event();
        if (current.type == KEY_PRESSED) {
            trapped = current.key;
        } else if (current.key == trapped) {
            return trapped;
        }
    }

    /*
    for (current = get_last_event(); current.type != KEY_PRESSED || current.key == NO_KEY;) {}
    keyboard_key key = current.key;
    terminal_writestring("Read press event: ");
    int crit = 0x1b;
    if (key < crit) {
        terminal_putchar('<');
    } else if (key > crit) {
        terminal_putchar('>');
    } else {
        terminal_putchar('=');
    }
    for (current = get_last_event(); current.type == KEY_PRESSED || current.key != key;) {}
    return key;
    */
}

bool key_is_char(keyboard_key key) {
    return key_to_char(key) != '\0';
}

char key_to_char(keyboard_key key) {
    switch (key) {
        case KEY_0:
        case KEY_KEYPAD_0:
            return '0';
        case KEY_1:
        case KEY_KEYPAD_1:
            return '1';
        case KEY_2:
        case KEY_KEYPAD_2:
            return '2';
        case KEY_3:
        case KEY_KEYPAD_3:
           return '3';
        case KEY_4:
        case KEY_KEYPAD_4:
           return '4';
        case KEY_5:
        case KEY_KEYPAD_5:
           return '5';
        case KEY_6:
        case KEY_KEYPAD_6:
           return '6';
        case KEY_7:
        case KEY_KEYPAD_7:
           return '7';
        case KEY_8:
        case KEY_KEYPAD_8:
           return '8';
        case KEY_9:
        case KEY_KEYPAD_9:
           return '9';
        case KEY_A:
          return 'A';
        case KEY_B:
          return 'B';
        case KEY_C:
          return 'C';
        case KEY_D:
          return 'D';
        case KEY_E:
          return 'E';
        case KEY_F:
          return 'F';
        case KEY_G:
          return 'G';
        case KEY_H:
          return 'H';
        case KEY_I:
          return 'I';
        case KEY_J:
          return 'J';
        case KEY_K:
          return 'K';
        case KEY_L:
          return 'L';
        case KEY_M:
          return 'M';
        case KEY_N:
          return 'N';
        case KEY_O:
          return 'O';
        case KEY_P:
          return 'P';
        case KEY_Q:
          return 'Q';
        case KEY_R:
          return 'R';
        case KEY_S:
          return 'S';
        case KEY_T:
          return 'T';
        case KEY_U:
          return 'U';
        case KEY_V:
          return 'V';
        case KEY_W:
          return 'W';
        case KEY_X:
          return 'X';
        case KEY_Y:
          return 'Y';
        case KEY_Z:
          return 'Z';
        case KEY_MINUS:
        case KEY_KEYPAD_MINUS:
          return '-';
        case KEY_KEYPAD_PLUS:
          return '+';
        case KEY_LEFT_SQUARE_BRACKET:
          return '[';
        case KEY_RIGHT_SQUARE_BRACKET:
          return ']';
        case KEY_SEMICOLON:
          return ';';
        case KEY_COMMA:
          return ',';
        case KEY_BACKSLASH:
          return '\\';
        case KEY_BACKTICK:
          return '`';
        case KEY_PERIOD:
          return '.';
        case KEY_FORWARD_SLASH:
          return '/';
        case KEY_SPACEBAR:
          return ' ';
        case KEY_EQUALS:
          return '=';
        case KEY_ENTER:
        case KEY_KEYPAD_ENTER:
          return '\n';
        default:
          return '\0';
    }
}
