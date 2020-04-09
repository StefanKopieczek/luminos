#ifndef _ADDRESSES_H
#define ADDRESSES_H

#define VGA_BUFFER  (void *) 0x000B8000
#define RAM_START   (void *) 0x00100000
#define GDT_ADDR    RAM_START
#define HEAP_START  (void *) 0x00200000
#define RAM_END     (void *) 0x00e00000
#define HEAP_END    RAM_END

#endif
