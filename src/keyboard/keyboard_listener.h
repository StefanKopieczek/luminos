#ifndef _KEYBOARD_LISTENER_H
#define _KEYBOARD_LISTENER_H

typedef struct keyboard_listener_node {
    keyboard_listener listener;
    struct keyboard_listener_node *next;
} keyboard_listener_node;

void fire_keyboard_event(keyboard_event *);

#endif
