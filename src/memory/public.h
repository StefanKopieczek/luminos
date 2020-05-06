#ifndef _MEMORY_H
#define _MEMORY_H
#include <stddef.h>

#define INVALID_ADDR (void *)-1

void memory_init();
void *malloc(size_t size);
void free(void *p);
void memcpy(void *dest, const void *src, size_t len);
void memset(void *dest, char value, size_t len);

#endif
