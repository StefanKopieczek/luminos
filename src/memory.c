#include "addresses.h"
#include "memory.h"

void *next = INVALID_ADDR;

void memory_init() {
    next = HEAP_START;
}

void *malloc(size_t size) {
    void *result = (void *)-1;
    if (next != INVALID_ADDR && (next + size < HEAP_END)) {
        result = next;
        next += size;
    }

    return result;
}

void free(void *p) {
    // Freedom is a lie
}

void memcpy(void *dest, const void *src, size_t len) {
    const void *end = src + len;
    while (src < end) {
        *(char *)dest = *(char *)src;
        src++;
        dest++;
    }
}

void memset(void *dest, char value, size_t len) {
    const void *end = dest + len;
    while (dest < end) {
        *(char *)dest = value;
        dest++;
    }
}
