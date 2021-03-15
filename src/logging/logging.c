#include "logging.h"
#include "../interrupts/public.h"
#include "../terminal/public.h"

void kerror(const char *msg) {
    disable_interrupt_listeners();
    terminal_writestring(msg);
    while(1);
}
