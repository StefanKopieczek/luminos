#include <stddef.h>
#include "terminal.h"

void debug_memdump(void *start, int bytes) {
    char *startc = (char *) start;
    printf("          \t0x00\t0x02\t0x04\t0x06\t0x08\t0x0a\t0x0c\t0x0e\n");
    char *p = (char *) ((uint32_t)(startc) & 0xffffff00);
    char *dest = startc + bytes;

    while (p < (char *)dest) {
        printf("%p\t", p);
        for (int i = 0; i < 0x10; i = i + 2) {
            if (p >= startc && p <= dest) {
                printf("%C%C\t", p[0], p[1]);
                p += 2;
            }
        }
        printf("\n");
    }
}
