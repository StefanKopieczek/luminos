#ifndef _KEYBOARD_H
#define _KEYBOARD_H

#include <stdint.h>

void register_for_interrupts();
void interrupt_handler(int);
keyboard_event *get_current_event();

#endif
