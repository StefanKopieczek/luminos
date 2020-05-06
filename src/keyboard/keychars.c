#include "public.h"

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

