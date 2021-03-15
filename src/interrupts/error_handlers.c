#include "public.h"
#include "../logging/public.h"

void on_divide_by_zero(int);
void on_debug(int);
void on_non_maskable(int);
void on_breakpoint(int);
void on_overflow(int);
void on_bound_range_exceeded(int);
void on_invalid_opcode(int);
void on_device_not_available(int);
void on_double_fault(int);
void on_coprocessor_segment_overrun(int);
void on_invalid_tss(int);
void on_segment_not_present(int);
void on_general_protection_fault(int);
void on_page_fault(int);
void on_x87_floating_point_exception(int);
void on_alignment_check(int);
void on_machine_check(int);
void on_simd_floating_point_exception(int);
void on_virtualization_exception(int);
void on_security_exception(int);

void init_default_error_handlers() {
    register_interrupt_listener(INT_DIVIDE_BY_ZERO, &on_divide_by_zero);
    register_interrupt_listener(INT_DEBUG, &on_debug);
    register_interrupt_listener(INT_NON_MASKABLE, &on_non_maskable);
    register_interrupt_listener(INT_BREAKPOINT, &on_breakpoint);
    register_interrupt_listener(INT_OVERFLOW, &on_overflow);
    register_interrupt_listener(INT_BOUND_RANGE_EXCEEDED, &on_bound_range_exceeded);
    register_interrupt_listener(INT_INVALID_OPCODE, &on_invalid_opcode);
    register_interrupt_listener(INT_DEVICE_NOT_AVAILABLE, &on_device_not_available);
    register_interrupt_listener(INT_DOUBLE_FAULT, &on_double_fault);
    register_interrupt_listener(INT_COPROCESSOR_SEGMENT_OVERRUN, &on_coprocessor_segment_overrun);
    register_interrupt_listener(INT_INVALID_TSS, on_invalid_tss);
    register_interrupt_listener(INT_SEGMENT_NOT_PRESENT, &on_segment_not_present);
    register_interrupt_listener(INT_GENERAL_PROTECTION_FAULT, &on_general_protection_fault);
    register_interrupt_listener(INT_PAGE_FAULT, &on_page_fault);
    register_interrupt_listener(INT_X87_FLOATING_POINT_EXCEPTION, &on_x87_floating_point_exception);
    register_interrupt_listener(INT_ALIGNMENT_CHECK, &on_alignment_check);
    register_interrupt_listener(INT_MACHINE_CHECK, &on_machine_check);
    register_interrupt_listener(INT_SIMD_FLOATING_POINT_EXCEPTION, &on_simd_floating_point_exception);
    register_interrupt_listener(INT_VIRTUALIZATION_EXCEPTION, &on_virtualization_exception);
    register_interrupt_listener(INT_SECURITY_EXCEPTION, &on_security_exception);
}

void on_divide_by_zero(int _interrupt) {
    kerror("A division by zero occurred!");
}

void on_debug(int _interrupt) {
    kerror("A debug interrupt occurred");
}

void on_non_maskable(int _interrupt) {
    kerror("A non-maskable interrupt occurred");
}

void on_breakpoint(int _interrupt) {
    kerror("A breakpoint interrupt occurred");
}

void on_overflow(int _interrupt) {
    kerror("A numerical overflow occurred!");
}

void on_bound_range_exceeded(int _interrupt) {
    kerror("Bound range exceeded!");
}

void on_invalid_opcode(int _interrupt) {
    kerror("An invalid opcode was reached by the processor!");
}

void on_device_not_available(int _interrupt) {
    kerror("A device-not-available exception occurred!");
}

void on_double_fault(int _interrupt) {
    kerror("A double fault occurred");
}

void on_coprocessor_segment_overrun(int _interrupt) {
    kerror("Coprocessor segment overrrun");
}

void on_invalid_tss(int _interrupt) {
    kerror("Error - TSS invalid!");
}

void on_segment_not_present(int _interrupt) {
    kerror("Segment not present!");
}

void on_stack_segment_fault(int _interrupt) {
    kerror("Stack segment fault!");
}

void on_general_protection_fault(int _interrupt) {
    kerror("General protection fault!");
}

void on_page_fault(int _interrupt) {
    kerror("Page fault!");
}

void on_x87_floating_point_exception(int _interrupt) {
    kerror("An x87 floating point exception occurred");
}

void on_alignment_check(int _interrupt) {
    kerror("An alignment check occurred");
}

void on_machine_check(int _interrupt) {
    kerror("A machine check occurred");
}

void on_simd_floating_point_exception(int _interrupt) {
    kerror("A SIMD floating point exception occurred");
}

void on_virtualization_exception(int _interrupt) {
    kerror("A virtualization exception occurred");
}

void on_security_exception(int _interrupt) {
    kerror("A security exception occurred!");
}

