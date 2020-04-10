#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>

char *int2dec(int);
char *int2hex(int);
char *int2str(int n, int base);
char *strncat(char *dest, const char *src, int n);
size_t strlen(const char *);

#endif
