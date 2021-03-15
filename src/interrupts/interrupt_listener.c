#include <stdbool.h>
#include "public.h"
#include "interrupt.h"
#include "interrupt_listener.h"
#include "../logging/public.h"
#include "../memory/public.h"

static interrupt_listener_node *listeners[NUM_INTERRUPTS];
static bool interrupt_listeners_enabled;

void init_interrupt_listener_queues() {
    memset(listeners, 0, sizeof(interrupt_listener_node *) * NUM_INTERRUPTS);
    interrupt_listeners_enabled = false;
}

void enable_interrupt_listeners() {
    interrupt_listeners_enabled = true;
}

void disable_interrupt_listeners() {
    interrupt_listeners_enabled = false;
}

void register_interrupt_listener(int interrupt, interrupt_listener listener) {
    interrupt_listener_node **last_ptr = &listeners[interrupt];
    while (*last_ptr) {
        last_ptr = &((*last_ptr)->next);
    }

    *last_ptr = malloc(sizeof(interrupt_listener_node));
    interrupt_listener_node *new_node = *last_ptr;
    new_node->listener = listener;
    new_node->next = 0;
}

void unregister_interrupt_listener(int interrupt, interrupt_listener listener) {
    if (!listeners[interrupt]) {
        kerror("Unable to unregister interrupt listener, as it was not found (in fact, that interrupt had none at all)");
    }

    interrupt_listener_node **parent_link = &listeners[interrupt];
    while ((*parent_link)->next) {
        if ((*parent_link)->next->listener == listener) {
            interrupt_listener_node *match = (*parent_link)->next;
            *parent_link = match->next;
            free(match);
            return;
        }
    }

    kerror("Unable to unregister interrupt listener, as it was not found");
}

void fire_interrupt_event(int interrupt) {
    if (!interrupt_listeners_enabled) {
        return;
    }

    interrupt_listener_node *current = listeners[interrupt];
    while (current) {
        current->listener(interrupt);
        current = current->next;
    }
}
