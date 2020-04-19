#include <stdbool.h>
#include <stdint.h>

#include "addresses.h"
#include "memory.h"
#include "gdt.h"

// Readability definitions for boolean params.
#define GROWS_UP          true
#define GROWS_DOWN        false
#define CONFORMS          true
#define DOES_NOT_CONFORM  false
#define IS_READABLE       true
#define IS_NOT_READABLE   false
#define IS_WRITEABLE      true
#define IS_NOT_WRITEABLE  false

#define CODE_SEGMENT_TYPE 0x03
#define DATA_SEGMENT_TYPE 0x02
#define TASK_SEGMENT_TYPE 0x01

typedef struct {
    uint16_t size_plus_one;
    uint32_t table_address;
} gdt_desc;

typedef struct {
    uint16_t limit_lower_bits;
    uint16_t base_lower_bits;
    uint8_t base_mid_bits;

    // Bit structure: [gs00llll]
    // g - use_page_granularity (if 1, limit is in 4KiB blocks; if 0, in 1B blocks)
    // s - enable_32_bit_mode (if 1, selector defines 32-bit protected mode; if 0, 16-bit).
    // 0 - must be set to 0.
    // l - the most-significant bits of the 'limit' value. the LSBs are in limit_lower_bits.
    uint8_t flags_and_limit;

    // Bit structure: [prrttdra]
    // p - 'present' bit (must be 1)
    // r - ring level from which the segment can be accessed (but see 'direction_conform')
    // t - descriptor type (see <X>_SEGMENT_TYPE defines above for values)
    // d - direction/conform bit:
    //      * If data selector, 0 if the segment grows up, 1 if it grows down
    //      * If code selector, 0 if the code can only be executed from the 'ring level' set above,
    //        and 1 if it can be executed from an _equal or lower_ ring level.
    // r - read/write bit:
    //      * If code selector, whether read access is allowed (write is never allowed)
    //      * If data selector, whether write access is allowed (read is always allowed)
    // a - accessed bit - initial value irrelevant. Set to 1 by the CPU when the segment is accessed.
    uint8_t access;

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
    write_null_entry(gdt_table++);
    write_code_entry(gdt_table++, 0x0, 0xffffffff, IS_NOT_READABLE, CONFORMS, 0);
    write_data_entry(gdt_table++, 0x0, 0xffffffff, IS_WRITEABLE, GROWS_UP, 0);

    const int num_entries = (gdt_table - (gdt_entry *)GDT_ADDR);
    gdt_desc *descriptor = (gdt_desc *) GDT_DESC_ADDR;
    descriptor->size_plus_one = num_entries + 1;
    descriptor->table_address = (uint32_t) GDT_ADDR;

    asm("lgdt (%0)" :: "r" (&descriptor));
}

void write_base(gdt_entry *entry, uint32_t base) {
    entry->base_lower_bits = base & 0xffff;
    base >>= 16;
    entry->base_mid_bits = base & 0xff;
    entry->base_upper_bits = base >> 8;
}

void write_limit(gdt_entry *entry, uint32_t limit) {
    // The lower 16 bits of the limit have their own field in the struct.
    // The upper 4 bits are stored in the lower nibble of entry->flags_and_limit.
    // TODO check that limit is in the encodable range (20 bits).
    entry->limit_lower_bits = limit & 0xffff;
    entry->flags_and_limit = (entry->flags_and_limit & 0xf0) | (limit >> 16);
}

void set_present(gdt_entry *entry, bool is_present) {
    // The 'present' bit is the MSB of entry->access.
    if (is_present) {
        entry->access |= 0x80;
    } else {
        entry->access &= 0x7f;
    }
}

void set_ring_level(gdt_entry *entry, uint8_t ring_level) {
    // The ring level is stored in bits 5 and 6 of entry->access.
    // TODO: Ensure it's within range.
    ring_level &= 0x03;
    entry->access = (entry->access & 0x9f) | (ring_level << 5);
}

void set_type(gdt_entry *entry, uint8_t segment_type) {
    // The segment type is stored in bits 3 and 4 of entry->access.
    // TODO ensure it's in range.
    segment_type &= 0x03;
    entry->access = (entry->access & 0xe7) | (segment_type << 3);
}

void set_direction_conform(gdt_entry *entry, bool should_set) {
    // The direction/conform bit is bit 2 of entry->access.
    if (should_set) {
        entry->access |= 0x04;
    } else {
        entry->access &= 0xfb;
    }
}

void set_read_write(gdt_entry *entry, bool enabled) {
    // The read/write enable bit is bit 1 of entry->access.
    if (enabled) {
        entry->access |= 0x02;
    } else {
        entry->access &= 0xfd;
    }
}

void set_accessed(gdt_entry *entry, bool accessed) {
    // The accessed bit is the LSB of entry->access.
    if (accessed) {
        entry->access |= 0x01;
    } else {
        entry->access &= 0xfe;
    }
}

void set_page_granularity(gdt_entry *entry, bool use_page_granularity) {
    // The granularity bit is bit 7 of entry->flags_and_limit.
    if (use_page_granularity) {
        entry->flags_and_limit |= 0x80;
    } else {
        entry->flags_and_limit &= 0x7f;
    }
}

void set_32_bit_enabled(gdt_entry *entry, bool use_32_bit_mode) {
    // The size bit is bit 6 of entry->flags_and_limit.
    if (use_32_bit_mode) {
        entry->flags_and_limit |= 0x40;
    } else {
        entry->flags_and_limit &= 0xbf;
    }
}

void set_zero_bits(gdt_entry *entry) {
    // Bits 4 and 5 of entry->flags_and_limit should always be 0.
    entry->flags_and_limit &= 0xcf;
}

void write_common_flags(gdt_entry *entry) {
   set_zero_bits(entry);
   set_accessed(entry, false);
   set_32_bit_enabled(entry, true);
   set_page_granularity(entry, true);
   set_present(entry, true);
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
    set_read_write(entry, is_readable);
    set_direction_conform(entry, is_conforming);
    set_type(entry, CODE_SEGMENT_TYPE);
    set_ring_level(entry, ring_level);
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
    set_read_write(entry, is_writeable);
    set_direction_conform(entry, grows_down);
    set_type(entry, DATA_SEGMENT_TYPE);
    set_ring_level(entry, ring_level);
}

void write_system_entry(gdt_entry *entry,
        uint32_t base,
        uint32_t limit,
        uint8_t ring_level) {
    write_common_flags(entry);
    write_base(entry, base);
    write_limit(entry, limit);

    set_type(entry, TASK_SEGMENT_TYPE);
    set_ring_level(entry, ring_level);

    // Unsure what meaning these have for system segments...
    set_read_write(entry, false);
    set_direction_conform(entry, true);
}

