#include <stdint.h>

#include "public.h"
#include "keyboard.h"
#include "keyboard_listener.h"
#include "scancodes.h"
#include "../interrupts/public.h"
#include "../logging/public.h"
#include "../memory/public.h"
#include "../ports/public.h"
#include "../terminal/public.h"

static keyboard_event scanCodes[256];

void init_keyboard() {
    write_scancodes_map_1(scanCodes);
    register_for_interrupts();
}

void register_for_interrupts() {
    get_current_event(0x60);
    register_interrupt_listener(INT_IRQ1, &interrupt_handler);
    get_current_event(0x60);
}

void interrupt_handler(int interrupt) {
    if (interrupt != INT_IRQ1) {
        kerror("Programmer error - keyboard handler called for interrupt other than IRQ1");
    }
    keyboard_event *event = get_current_event();
    fire_keyboard_event(event);
}

keyboard_event *get_current_event() {
    return &scanCodes[port_read(0x60)];
}
