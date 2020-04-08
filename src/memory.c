#include "memory.h"

void *next = INVALID_ADDR;

void memory_init() {
    next = RAM_START;
}

void *malloc(size_t size) {
    void *result = (void *)-1;
    if (next != INVALID_ADDR && (next + size < RAM_END)) {
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
        *(int *)dest = *(int *)src;
        src++;
        dest++;
    }
}
