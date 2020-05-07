#ifndef _INTERRUPT_LISTENER_H
#define _INTERRUPT_LISTENER_H

typedef struct interrupt_listener_node {
    interrupt_listener listener;
    struct interrupt_listener_node *next;
} interrupt_listener_node;

void init_interrupt_listener_queues();
void fire_interrupt_event(int interrupt);

#endif
