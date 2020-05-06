#ifndef _ADDRESSES_H
#define ADDRESSES_H

#define RAM_START     ((void *) 0x00000500)
#define GDT_DESC_ADDR RAM_START
#define GDT_ADDR      (RAM_START + 16)
#define IDT_DESC_ADDR (GDT_ADDR + 0x100)
#define IDT_ADDR      (IDT_DESC_ADDR + 16)
#define HEAP_START    (IDT_ADDR + 0x2000)
#define RAM_END       ((void *) 0x00007BFF)
#define HEAP_END      RAM_END
#define VGA_BUFFER    ((void *) 0x000B8000)

#endif
