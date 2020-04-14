#include <stdarg.h>
#include <stdbool.h>
#include "string.h"
#include "memory.h"

char get_char_for_digit(int d) {
    if (d <= 9) {
        // The digits 0-9 are contiguous in ASCII starting at code 0x30.
        return 0x30 + d;
    } else if (d <= 16) {
        // The letters a-z are contiguous starting at 0x61.
        return 0x57 + d;
    } else {
        return '?';
    }
}

char *int2dec(int n) {
    return int2str(n, 10);
}

char *int2hex(int n) {
    const char *raw_result = int2str(n, 16);

    int digits = strlen(raw_result);
    char *result = malloc(digits + 3);
    if (result == INVALID_ADDR) {
        return (char *)INVALID_ADDR;
    }

    memcpy(result, "0x", 3);
    return strncat(result, raw_result, digits);
}

char *int2str(int n, int base) {
    // TODO check base <= 16.

    // Worst case is base 2, where each digit (each bit) will need a char.
    // That makes 32 bytes, and we need one for \0 as well.
    char *result = malloc(33);

    bool negative = n < 0;
    if (negative) {
        n *= -1;
    }

    result[32] = '\0';
    result[31] = '0';
    char *digit;
    for (digit = result + 31; n > 0; digit--) {
        *digit = get_char_for_digit(n % base);
        n /= base;
    }

    if (negative) {
        *(digit--) = '-';
    }

    return digit + 1;
}

char *strncat(char *dest, const char *src, int n) {
    int destlen = strlen(dest);
    int i;
    for (i = 0; i < n; i++) {
        dest[destlen + i] = src[i];
        if (src[i] == '\0') {
            break;
        }
    }
    if (src[i] != '\0') {
        dest[destlen + i + 1] = '\0';
    }

    return dest;
}

char *strcat(char *dest, const char *src) {
    char *p = dest;
    while(*p)
        p++;

    while(*src)
        *(p++) = *(src++);

    *p = '\0';
    return dest;
}

char *strcpy(char *dest, const char *src) {
    char *p = dest;
    while (*src)  {
        *(p++) = *(src++);
    }
    return dest;
}

size_t strlen(const char* str) {
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

void strappend(char **buf, const char *src) {
    while (*src) {
        *((*buf)++) = *(src++);
    }
    **buf = '\0';
}

int sprintf(char *buf, const char *format, ...) {
    va_list argp;
    va_start(argp, format);
    char *result = buf;
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            if (*format == 's') {
                const char *param = va_arg(argp, const char *);
                strappend(&buf, param);
            } else if (* format == 'd') {
                int param = va_arg(argp, int);
                strappend(&buf, int2dec(param));
            } else if (*format == 'x') {
                int param = va_arg(argp, int);
                strcpy(buf, int2hex(param));
                strappend(&buf, int2hex(param));
            } else {
                // TODO error handling
                strappend(&buf, "<unknown param type>");
            }
        } else {
            *(buf++) = *format;
        }
        format++;
    }
    buf = '\0';
    return strlen(result);
}
