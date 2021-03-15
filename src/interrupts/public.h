#ifndef _INTERRUPT_PUBLIC_H
#define _INTERRUPT_PUBLIC_H

#define INT_DIVIDE_BY_ZERO 0x00
#define INT_DEBUG 0x01
#define INT_NON_MASKABLE 0x02
#define INT_BREAKPOINT 0x03
#define INT_OVERFLOW 0x04
#define INT_BOUND_RANGE_EXCEEDED 0x05
#define INT_INVALID_OPCODE 0x06
#define INT_DEVICE_NOT_AVAILABLR 0x07
#define INT_DOUBLE_FAULT 0x08
#define INT_COPROCESSOR_SEGMENT_OVERRUN 0x09
#define INT_INVALID_TSS 0x0a
#define INT_SEGMENT_NOT_PRESENT 0x0b
#define INT_STACK_SEGMENT_FAULT 0x0c
#define INT_GENERAL_PROTECTION_FAULT 0x0d
#define INT_PAGE_FAULT 0x0e
#define INT_X87_FLOATING_POINT_EXCEPTION 0x10
#define INT_ALIGNMENT_CHECK 0x11
#define INT_MACHINE_CHECK 0x12
#define INT_SIMD_FLOATING_POINT_EXCEPTION 0x13
#define INT_VIRTUALIZATION_EXCEPTION 0x13
#define INT_SECURITY_EXCEPTION 0x1e
#define INT_IRQ0 0x20
#define INT_IRQ1 0x21
#define INT_IRQ2 0x22
#define INT_IRQ3 0x23
#define INT_IRQ4 0x24
#define INT_IRQ5 0x25
#define INT_IRQ6 0x26
#define INT_IRQ7 0x27
#define INT_IRQ8 0x28
#define INT_IRQ9 0x29
#define INT_IRQ10 0x2a
#define INT_IRQ11 0x2b
#define INT_IRQ12 0x2c
#define INT_IRQ13 0x2d
#define INT_IRQ14 0x2e
#define INT_IRQ15 0x2f

typedef void (*interrupt_listener)(int interrupt);

void init_interrupts();
void register_interrupt_listener(int interrupt, interrupt_listener);
void unregister_interrupt_listener(int interrupt, interrupt_listener);
void enable_interrupt_listeners();
void disable_interrupt_listeners();

#endif
