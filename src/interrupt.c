#include "addresses.h"
#include "interrupt.h"
#include "memory.h"
#include "port.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PIC_MASTER_CMD_PORT 0x20
#define PIC_MASTER_DATA_PORT 0x21
#define PIC_SLAVE_CMD_PORT 0xa0
#define PIC_SLAVE_DATA_PORT 0xa1
#define PIC_INIT_CMD 0x11
#define PIC_EOI_CMD 0x20

#define TASK_GATE 0x15
#define INTERRUPT_GATE 0x0e
#define TRAP_GATE 0x0f

// A selector for a GDT segment.
// Bit field: [iiiiiiiiiiiitrr]
// i - index of the entry in the GDT/LDT
// t - 0 if GDT, 1 if LDT
// r - ring level to use to access the descriptor
// So for example, 0x08 = 0b000000000001000 indicates access to GDT index 1 in the GDT
// with ring level zero.
#define CODE_SELECTOR 0x08

#define KERNEL_ONLY 0

typedef struct {
	uint16_t size;
	uint32_t address;
} __attribute__((packed)) idt_desc;

typedef struct {
    uint16_t isr_address_lsb;
    uint16_t gdt_selector; // A segment selector bitfield (see CODE_SELECTOR comment above)
    uint8_t zero;

    // Bit structure [appttttt]
    // a - is enabled (1 = enabled)
    // p - descriptor privilege level
    // t - gate type
    uint8_t info;

    uint16_t isr_address_msb;
} __attribute__((packed)) idt_entry;

// The following are defined in interrupt_handlers.s.
extern int load_idt(); // Expects a pointer to an idt_desc, and loads the corresponding IDT.
extern int irq0(); // The remaining methods are stub interrupt handlers that delegate to the
extern int irq1(); // handler methods in this file.
extern int irq2();
extern int irq3();
extern int irq4();
extern int irq5();
extern int irq6();
extern int irq7();
extern int irq8();
extern int irq9();
extern int irq10();
extern int irq11();
extern int irq12();
extern int irq13();
extern int irq14();
extern int irq15();
extern int do_nothing();

// Forward definitions
void remap_pics();
void init_idt();
void write_task_gate_entry(idt_entry *dest, void *isr_address, uint16_t selector, uint8_t descriptor_privilege_level);
void write_trap_gate_entry(idt_entry *dest, void *isr_address, uint16_t selector, uint8_t descriptor_privilege_level);
void write_interrupt_gate_entry(idt_entry *dest, void *isr_address, uint16_t selector, uint8_t descriptor_privilege_level);
void set_common_fields(idt_entry *);
void set_isr_address(idt_entry *entry, void *isr_address);
void set_enabled(idt_entry *entry, bool is_enabled);
void set_descriptor_privilege_level(idt_entry *entry, uint8_t descriptor_privilege_level);
void set_gate_type(idt_entry *entry, uint8_t gate_type);
void send_master_eoi();
void send_master_and_slave_eoi();

void init_interrupts() {
    remap_pics();
  	init_idt();
}

/*
 * By default, the BIOS maps the master PIC to interrupts 0x08-0x0f, and the slave to 0x70-0x77.
 * However, the CPU reserves 0x00->0x1f for CPU exceptions, so in the initial configuration, the IRQs from
 * the PICs will conflict with CPU exceptions, and our interrupt handler would have to try and figure out whether
 * a given interrupt came from the CPU or the IRQ line.
 * Instead, it's easier to remap the PICs to a different interrupt range.
 * We'll remap the master PIC to 0x20->0x27, and the slave to 0x28->0x2f so that they're contiguous.
 * For more information on PIC initialization and wiring see:
 *  - https://wiki.osdev.org/PIC
 *  - http://www.thesatya.com/8259.html
 */
void remap_pics() {
	// In this method we'll alternate calls to the master and slave PIC.
	// This isn't just to be perverse - you need to wait an IO cycle between commands to ensure
	// the CPU has actually completed the operation.
    // Alternatively there are hacks that busy-wait for one IO cycle, but this is probably easier.

	// Send init commands to the PICs.
    // They'll now wait for three successive initialization bytes:
    // 1) The interrupt vector offset (the offset that PIC should use for its first IRQ)
    // 2) A byte describing how the master and slave are chained.
    // 3) A mode byte that controls other details of the operation
	port_write(PIC_MASTER_CMD_PORT, PIC_INIT_CMD);
	port_write(PIC_SLAVE_CMD_PORT, PIC_INIT_CMD);

	// Wire master->0x20 and slave->0x28
	port_write(PIC_MASTER_DATA_PORT, 0x20);
	port_write(PIC_SLAVE_DATA_PORT, 0x28);

	// Set up chaining:
    // - Tell the master PIC that the slave is connected to the IRQ2 input of the master
    // - Give the slave ID number '2' (not sure exactly what this means but it seems conventional)
	port_write(PIC_MASTER_DATA_PORT, 0b00000100);
	port_write(PIC_SLAVE_DATA_PORT, 0x02);

	// Set both PICs to 8086/88 (MCS-80/85) mode.
	port_write(PIC_MASTER_DATA_PORT, 0x01);
	port_write(PIC_SLAVE_DATA_PORT, 0x01);

	// The initialization bytes have now been sent.
    // There's one more thing to do - re-enable the IRQ lines on the pics so they resume sending interrupts.
    // Oddly this seems to be done by writing to the data port rather than the command port.
    // I can't find documentation, but from examples it seems like each bit corresponds to an IRQ line,
    // with low bits indicating the line should be enabled, and high bits indicating it should be disabled.
	port_write(PIC_MASTER_DATA_PORT, 0xfd); // TODO set these to 0x00 to actually enable them
	port_write(PIC_SLAVE_DATA_PORT, 0xff);
}

void init_idt() {
	idt_entry *idt = (idt_entry *)IDT_ADDR;
    size_t idt_size = sizeof(idt_entry) * 256;
    memset(idt, 0xff, idt_size);

    // Initialize the IDT with do-nothing handlers for each interrupt.
    idt_entry default_entry;
    write_interrupt_gate_entry(&default_entry, (void *)do_nothing, CODE_SELECTOR, KERNEL_ONLY);
    for (int i = 0; i < 256; i++) {
        idt[i] = default_entry;
    }

    // Set up the IRQs, starting at IDT index 20 as that's where remap_pics() mapped them.
    idt_entry *p = &idt[0x20];
	write_interrupt_gate_entry(p++, (void *)irq0, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq1, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq2, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq3, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq4, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq5, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq6, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq7, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq8, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq9, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq10, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq11, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq12, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq13, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq14, CODE_SELECTOR, KERNEL_ONLY);
	write_interrupt_gate_entry(p++, (void *)irq15, CODE_SELECTOR, KERNEL_ONLY);

	idt_desc *desc = (idt_desc *)IDT_DESC_ADDR;
	desc->size = idt_size;
	desc->address = (uint32_t)IDT_ADDR;

    load_idt(desc);
}


void write_task_gate_entry(idt_entry *dest, void *isr_address, uint16_t selector, uint8_t descriptor_privilege_level) {
    set_common_fields(dest);
    set_isr_address(dest, isr_address);
    set_descriptor_privilege_level(dest, descriptor_privilege_level);
    set_gate_type(dest, TASK_GATE);
    dest->gdt_selector = selector;
}

void write_trap_gate_entry(idt_entry *dest, void *isr_address, uint16_t selector, uint8_t descriptor_privilege_level) {
    set_common_fields(dest);
    set_isr_address(dest, isr_address);
    set_descriptor_privilege_level(dest, descriptor_privilege_level);
    set_gate_type(dest, TRAP_GATE);
    dest->gdt_selector = selector;
}

void write_interrupt_gate_entry(idt_entry *dest, void *isr_address, uint16_t selector, uint8_t descriptor_privilege_level) {
    set_common_fields(dest);
    set_isr_address(dest, isr_address);
    set_descriptor_privilege_level(dest, descriptor_privilege_level);
    set_gate_type(dest, INTERRUPT_GATE);
    dest->gdt_selector = selector;
}

void set_common_fields(idt_entry *entry) {
    set_enabled(entry, true);
    entry->zero = 0;
}

void set_isr_address(idt_entry *entry, void *isr_address) {
    entry->isr_address_lsb = (0xffff) & (uint32_t) isr_address;
    entry->isr_address_msb = ((uint32_t) isr_address) >> 16;
}

void set_enabled(idt_entry *entry, bool is_enabled) {
    // The is_enabled flag is bit 7 (MSB) of entry->info.
    if (is_enabled) {
        entry->info |= 0x80;
    } else {
        entry->info *= 0x7f;
    }
}

void set_descriptor_privilege_level(idt_entry *entry, uint8_t dpl) {
    // The DPL is stored in bits 5 and 6 of entry->info.
    // TODO: Check 0<=dpl<4.
    dpl &= 0x03;
    entry->info = (entry->info & 0x9f) + (dpl << 5);
}

void set_gate_type(idt_entry *entry, uint8_t type) {
    // The gate type forms the last five bits of entry->info.
    // (Strictly, the highest of these, bit 4, is the 'storage segment' bit, but this
    // should be 1 if and only if the gate is a task gate, so it's effectively part of
    // the type).
    // TODO check gate type is in range.
    type &= 0x1f;
    entry->info = (entry->info & 0xe0) + type;
}

/*
 * Cancels the currently-firing IRQ on the master PIC.
 */
void send_master_eoi() {
    port_write(PIC_MASTER_CMD_PORT, PIC_EOI_CMD);
}

/*
 * Cancels the currently-firing IRQ on the slave PIC.
 */
void send_master_and_slave_eoi() {
	// Cancel the slave first, or the master will immediately refire.
	port_write(PIC_SLAVE_CMD_PORT, PIC_EOI_CMD);
	port_write(PIC_MASTER_CMD_PORT, PIC_EOI_CMD);
}

void irq0_handler() {
	send_master_eoi();
}

void irq1_handler() {
    /*uint32_t *p = (uint32_t *)(RAM_START - 4);
    (*p)++;*/
	send_master_eoi();
}

void irq2_handler() {
	send_master_eoi();
}

void irq3_handler() {
	send_master_eoi();
}

void irq4_handler() {
	send_master_eoi();
}

void irq5_handler() {
	send_master_eoi();
}

void irq6_handler() {
	send_master_eoi();
}

void irq7_handler() {
	send_master_eoi();
}

void irq8_handler() {
	send_master_and_slave_eoi();
}

void irq9_handler() {
	send_master_and_slave_eoi();
}

void irq10_handler() {
	send_master_and_slave_eoi();
}

void irq11_handler() {
	send_master_and_slave_eoi();
}

void irq12_handler() {
	send_master_and_slave_eoi();
}

void irq13_handler() {
	send_master_and_slave_eoi();
}

void irq14_handler() {
	send_master_and_slave_eoi();
}

void irq15_handler() {
	send_master_and_slave_eoi();
}
