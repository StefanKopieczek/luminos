#ifndef _ADDRESSES_H
#define ADDRESSES_H

#define RAM_START     (void *) 0x00000500
#define GDT_DESC_ADDR RAM_START
#define GDT_ADDR      RAM_START + 6
#define HEAP_START    RAM_START + 0x1000
#define RAM_END       (void *) 0x00007BFF
#define HEAP_END      RAM_END
#define VGA_BUFFER    (void *) 0x000B8000

#endif
