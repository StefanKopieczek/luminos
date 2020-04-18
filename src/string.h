#ifndef _STRING_H
#define _STRING_H
#include <stdarg.h>
#include <stddef.h>

char *int2dec(int);
char *int2hex(int);
char *int2str(int n, int base);
char *uint2dec(unsigned int);
char *uint2hex(unsigned int);
char *uint2str(unsigned int n, int base);
char *strcat(char *dest, const char *src);
char *strncat(char *dest, const char *src, int n);
char *strcpy(char *dest, const char *src);
void strappend(char **buf, const char *src);
size_t strlen(const char *);
int sprintf(char *buf, const char *format, ...);
int vsprintf(char *buf, const char *format, va_list args);

char *lpad(char *dest, const char *src, char padChar, int minLength);

#endif
