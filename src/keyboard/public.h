#ifndef _KEYBOARD_H
#define _KEYBOARD_H
#include <stdbool.h>

typedef int keyboard_event_type;

typedef int keyboard_key;

typedef struct {
    keyboard_key key;
    keyboard_event_type type;
} keyboard_event;

void init_keyboard();
keyboard_event get_last_event();
keyboard_key wait_for_key();
bool key_is_char(keyboard_key key);
char key_to_char(keyboard_key key);

#define KEY_PRESSED 1
#define KEY_RELEASED 0

#define NO_KEY                      0
#define KEY_ESCAPE                  1
#define KEY_1                       2
#define KEY_2                       3
#define KEY_3                       4
#define KEY_4                       5
#define KEY_5                       6
#define KEY_6                       7
#define KEY_7                       8
#define KEY_8                       9
#define KEY_9                       10
#define KEY_0                       11
#define KEY_MINUS                   12
#define KEY_EQUALS                  13
#define KEY_BACKSPACE               14
#define KEY_Q                       15
#define KEY_W                       16
#define KEY_E                       17
#define KEY_R                       18
#define KEY_T                       19
#define KEY_Y                       20
#define KEY_U                       21
#define KEY_I                       22
#define KEY_O                       23
#define KEY_P                       24
#define KEY_LEFT_SQUARE_BRACKET     25
#define KEY_RIGHT_SQUARE_BRACKET    26
#define KEY_ENTER                   27
#define KEY_LEFT_CONTROL            28
#define KEY_A                       29
#define KEY_S                       30
#define KEY_D                       31
#define KEY_F                       32
#define KEY_G                       33
#define KEY_H                       34
#define KEY_J                       35
#define KEY_K                       36
#define KEY_L                       37
#define KEY_SEMICOLON               38
#define KEY_SINGLE_QUOTE            39
#define KEY_BACKTICK                40
#define KEY_LEFT_SHIFT              41
#define KEY_BACKSLASH               42
#define KEY_Z                       43
#define KEY_X                       44
#define KEY_C                       45
#define KEY_V                       46
#define KEY_B                       47
#define KEY_N                       48
#define KEY_M                       49
#define KEY_COMMA                   50
#define KEY_PERIOD                  51
#define KEY_FORWARD_SLASH           52
#define KEY_RIGHT_SHIFT             53
#define KEY_KEYPAD_ASTERISK         54
#define KEY_LEFT_ALT                55
#define KEY_SPACEBAR                56
#define KEY_CAPSLOCK                57
#define KEY_F1                      58
#define KEY_F2                      59
#define KEY_F3                      60
#define KEY_F4                      61
#define KEY_F5                      62
#define KEY_F6                      63
#define KEY_F7                      64
#define KEY_F8                      65
#define KEY_F9                      66
#define KEY_F10                     67
#define KEY_NUMLOCK                 68
#define KEY_SCROLL_LOCK             69
#define KEY_KEYPAD_7                70
#define KEY_KEYPAD_8                71
#define KEY_KEYPAD_9                72
#define KEY_KEYPAD_MINUS            73
#define KEY_KEYPAD_4                74
#define KEY_KEYPAD_5                75
#define KEY_KEYPAD_6                76
#define KEY_KEYPAD_PLUS             77
#define KEY_KEYPAD_1                78
#define KEY_KEYPAD_2                79
#define KEY_KEYPAD_3                80
#define KEY_KEYPAD_0                81
#define KEY_KEYPAD_PERIOD           82
#define KEY_F11                     83
#define KEY_F12                     84
#define KEY_PREVIOUS_TRACK          85
#define KEY_NEXT_TRACK              86
#define KEY_KEYPAD_ENTER            87
#define KEY_RIGHT_CONTROL           88
#define KEY_MUTE                    89
#define KEY_CALCULATOR              90
#define KEY_PLAY                    91
#define KEY_STOP                    92
#define KEY_VOLUME_DOWN             93
#define KEY_VOLUME_UP               94
#define KEY_WWW_HOME                95
#define KEY_KEYPAD_FORWARD_SLASH    96
#define KEY_RIGHT_ALT               97
#define KEY_HOME                    98
#define KEY_UP                      99
#define KEY_PAGE_UP                 100
#define KEY_LEFT                    101
#define KEY_RIGHT                   102
#define KEY_END                     103
#define KEY_DOWN                    104
#define KEY_PAGE_DOWN               105
#define KEY_INSERT                  106
#define KEY_DELETE                  107
#define KEY_LEFT_GUI                108
#define KEY_RIGHT_GUI               109
#define KEY_APPS                    110
#define KEY_ACPI_POWER              111
#define KEY_ACPI_SLEEP              112
#define KEY_ACPI_WAKE               113
#define KEY_WWW_SEARCH              114
#define KEY_WWW_FAVORITES           115
#define KEY_WWW_REFRESH             116
#define KEY_WWW_STOP                117
#define KEY_WWW_FORWARD             118
#define KEY_WWW_BACK                119
#define KEY_MY_COMPUTER             120
#define KEY_EMAIL                   121
#define KEY_MEDIA_SELECT            122
#define KEY_PRINT_SCREEN            123
#define KEY_PAUSE_BREAK             124
#define KEY_TAB                     125

#endif
