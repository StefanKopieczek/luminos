#include <stdint.h>

#include "public.h"
#include "keyboard.h"
#include "keyboard_listener.h"
#include "scancodes.h"
#include "../memory/public.h"
#include "../ports/public.h"
#include "../terminal/public.h"

static keyboard_event scanCodes[256];

void init_keyboard() {
    write_scancodes_map_1(scanCodes);
    register_for_interrupts();
}

void register_for_interrupts() {
    // TODO - when it's possible to register for interrupts, implement this method.
}

void interrupt_handler(int interrupt) {
    // TODO: Check that interrupt is IRQ1
    keyboard_event *event = get_current_event();
    fire_keyboard_event(event);
}

keyboard_event *get_current_event() {
    return &scanCodes[port_read(0x60)];
}
