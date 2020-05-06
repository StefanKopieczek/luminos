#include <stddef.h>
#include "../terminal/public.h"

void debug_memdump(void *start, int bytes) {
    uint8_t *startc = (uint8_t *) start;
    printf("          \t0x00\t0x02\t0x04\t0x06\t0x08\t0x0a\t0x0c\t0x0e\n");
    uint8_t *p = (uint8_t *) ((uint32_t)(startc) & 0xfffffff0);
    uint8_t *dest = startc + bytes;

    while (p < dest) {
        printf("%p\t", p);
        for (int i = 0; i < 0x10; i = i + 2) {
            if (p >= startc && p <= dest) {
                printf("%C%C\t", p[0], p[1]);
            }
            p += 2;
        }
        printf("\n");
    }
}
