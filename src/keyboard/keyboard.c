#include <stdint.h>

#include "public.h"
#include "scancodes.h"
#include "../memory/public.h"
#include "../ports/public.h"
#include "../terminal/public.h"

static keyboard_event scanCodes[256];

void init_keyboard() {
    write_scancodes_map_1(scanCodes);
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
}
