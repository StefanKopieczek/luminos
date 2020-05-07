#include "public.h"
#include "interrupt.h"
#include "interrupt_listener.h"
#include "../memory/public.h"
#include "../terminal/public.h"

static interrupt_listener_node *listeners[NUM_INTERRUPTS];

void init_interrupt_listener_queues() {
    memset(listeners, 0, sizeof(interrupt_listener_node *) * NUM_INTERRUPTS);
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
        // TODO: kerror here
        return;
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

    // TODO: kerror here, as no interrupt was found
}

void fire_interrupt_event(int interrupt) {
    printf("Firing event for interrupt %d", interrupt);
    interrupt_listener_node *current = listeners[interrupt];
    while (current) {
        current->listener(interrupt);
        current = current->next;
    }
}
