#include <stdbool.h>
#include <stdint.h>

#include "addresses.h"
#include "memory.h"
#include "gdt.h"

#define ENABLE_32_BIT_MODE true
#define ENABLE_PAGE_GRANULARITY true

// Readability definitions for boolean params.
#define GROWS_UP          true
#define GROWS_DOWN        false
#define CONFORMS          true
#define DOES_NOT_CONFORM  false
#define IS_READABLE       true
#define IS_NOT_READABLE   false
#define IS_WRITEABLE      true
#define IS_NOT_WRITEABLE  false

typedef struct {
    uint16_t limit_lower_bits;
    uint16_t base_lower_bits;
    uint8_t base_mid_bits;
    bool accessed : 1;
    bool read_write : 1;
    bool direction_conform : 1;
    bool is_executable : 1;
    bool is_code_or_data : 1;
    uint8_t ring_level : 2;
    bool is_present : 1;
    uint8_t limit_upper_bits : 4;
    unsigned int always_zero : 2;
    bool enable_32_bit_mode : 1;
    bool use_page_granularity : 1;
    uint8_t base_upper_bits;
} gdt_entry;

// Forward definitions
void write_null_entry(gdt_entry *);
void write_code_entry(gdt_entry *,
        uint32_t base,
        uint32_t limit,
        bool is_readable,
        bool conforms,
        uint8_t ring_level);
void write_data_entry(gdt_entry *,
        uint32_t base,
        uint32_t limit,
        bool is_writeable,
        bool grows_down,
        uint8_t ring_level);
void write_system_entry(gdt_entry *,
        uint32_t base,
        uint32_t limit,
        uint8_t ring_level);

void init_gdt() {
    gdt_entry *gdt_table = GDT_ADDR;
    write_null_entry(&gdt_table[0]);
    write_code_entry(&gdt_table[1], 0x0, 0xffffffff, IS_NOT_READABLE, CONFORMS, 0);
    write_data_entry(&gdt_table[2], 0x0, 0xffffffff, IS_WRITEABLE, GROWS_UP, 0);
}

void write_common_flags(gdt_entry *entry) {
   entry->always_zero = 0;
   entry->accessed = false;
   entry->enable_32_bit_mode = ENABLE_32_BIT_MODE;
   entry->use_page_granularity = ENABLE_PAGE_GRANULARITY;
   entry->is_present = 1;
}

void write_base(gdt_entry *entry, uint32_t base) {
    entry->base_lower_bits = base & 0xffff;
    base >>= 16;
    entry->base_mid_bits = base & 0xff;
    entry->base_upper_bits = base >> 8;
}

void write_limit(gdt_entry *entry, uint32_t limit) {
    // TODO check that limit is in the encodable range (20 bits).
    entry->limit_lower_bits = limit & 0xffff;
    entry->limit_upper_bits = limit >> 16;
}

void write_null_entry(gdt_entry *entry) {
    memset(entry, 0, sizeof(gdt_entry));
}

void write_code_entry(gdt_entry *entry,
        uint32_t base,
        uint32_t limit,
        bool is_readable,
        bool is_conforming,
        uint8_t ring_level) {
    write_common_flags(entry);
    write_base(entry, base);
    write_limit(entry, limit);
    entry->read_write = is_readable;
    entry->direction_conform = is_conforming;
    entry->is_executable = true;
    entry->is_code_or_data = true;
    entry->ring_level = ring_level;
}

void write_data_entry(gdt_entry *entry,
        uint32_t base,
        uint32_t limit,
        bool is_writeable,
        bool grows_down,
        uint8_t ring_level) {
    write_common_flags(entry);
    write_base(entry, base);
    write_limit(entry, limit);
    entry->read_write = is_writeable;
    entry->direction_conform = grows_down;
    entry->is_executable = false;
    entry->is_code_or_data = true;
    entry->ring_level = ring_level;
}

void write_system_entry(gdt_entry *entry,
        uint32_t base,
        uint32_t limit,
        uint8_t ring_level) {
    write_common_flags(entry);
    write_base(entry, base);
    write_limit(entry, limit);

    entry->is_code_or_data = false;
    entry->ring_level = ring_level;

    // Unsure what meaning these have for system segments...
    entry->read_write = false;
    entry->direction_conform = true;
    entry->is_executable = true;
}

