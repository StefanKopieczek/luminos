#include "public.h"
#include "keyboard_listener.h"
#include "../logging/public.h"
#include "../memory/public.h"

static keyboard_listener_node *listeners = 0;

void register_keyboard_listener(keyboard_listener listener) {
    keyboard_listener_node **last_ptr = &listeners;
    while (*last_ptr) {
        last_ptr = &((*last_ptr)->next);
    }

    *last_ptr = malloc(sizeof(keyboard_listener_node));
    keyboard_listener_node *new_node = *last_ptr;
    new_node->listener = listener;
    new_node->next = 0;
}

void unregister_keyboard_listener(keyboard_listener listener) {
    if (!listeners) {
        kerror("Unable to unregister keyboard listener, as no listener was found (in fact, no listeners are registered");
        return;
    }

    keyboard_listener_node **parent_link = &listeners;
    while ((*parent_link)->next) {
        if ((*parent_link)->next->listener == listener) {
            keyboard_listener_node *match = (*parent_link)->next;
            *parent_link = match->next;
            free(match);
            return;
        }
    }

    kerror("Unable to unregister keyboard listener, as no listener was found");
}

void fire_keyboard_event(keyboard_event *event) {
    keyboard_listener_node *current = listeners;
    while (current) {
        current->listener(*event);
        current = current->next;
    }
}
