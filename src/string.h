#ifndef _STRING_H
#define _STRING_H
#include <stddef.h>

char *int2dec(int);
char *int2hex(int);
char *int2str(int n, int base);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, int n);
char *strcpy(char *dest, const char *src);
void strappend(char **buf, const char *src);
size_t strlen(const char *);
int sprintf(char *buf, const char *format, ...);

#endif
