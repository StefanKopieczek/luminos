#include "public.h"
#include "../strings/public.h"
#include "../terminal/public.h"

const char* text = ""
	" _                     _       _____ _____ \n"
	"| |                   (_)     |  _  /  ___|\n"
	"| |    _   _ _ __ ___  _ _ __ | | | \\ `--. \n"
	"| |   | | | | '_ ` _ \\| | '_ \\| | | |`--. \\\n"
	"| |___| |_| | | | | | | | | | \\ \\_/ /\\__/ /\n"
	"\\_____/\\__,_|_| |_| |_|_|_| |_|\\___/\\____/ \n";

const char* art = ""
    "        #########::::::::::########\n"
    "        ##########::::::::#########\n"
    "        ###########::::::##########\n"
    "        ###########,---.###########\n"
    "        ##########/`---'\\##########\n"
    "        #########/       \\#########\n"
    "        ########/         \\########\n"
    "        #######:`-._____.-':#######\n"
    "        ######::::: ( ) |::::######\n"
    "        #####:::::: ) ( o:::::#####\n"
    "        ####::::: .-(_)-. :::::####\n"
    "        ###:::::: '=====' ::::::###\n";

void draw_char(char c) {
    switch (c) {
        case '#':
            terminal_setcolor(VGA_COLOR_LIGHT_BROWN);
            break;
        case ':':
            terminal_setcolor(VGA_COLOR_LIGHT_GREY);
            break;
        case(','):
        case('.'):
        case('-'):
        case('/'):
        case('\\'):
        case('`'):
        case('\''):
        case('_'):
        case('<'):
        case('='):
            terminal_setcolor(VGA_COLOR_LIGHT_MAGENTA);
            break;
        case('('):
        case(')'):
        case('|'):
        case('o'):
            terminal_setcolor(VGA_COLOR_WHITE);
            break;
        default:
            terminal_setcolor(VGA_COLOR_DARK_GREY);
    }

    terminal_putchar(c);
}

void splash_draw_lamp() {
    for (size_t i = 0; i < strlen(art); i++) {
        draw_char(art[i]);
    }
    terminal_setcolor(VGA_COLOR_WHITE);
}

void splash_draw_luminos() {
	terminal_setcolor(VGA_COLOR_WHITE);
	for (size_t i = 0; i < strlen(text); i++) {
		terminal_putchar(text[i]);
	}
}
