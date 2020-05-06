#ifndef __PORT_H
#define __PORT_H

#include <stdint.h>

void port_write(uint16_t port, uint8_t val);
uint8_t port_read(uint16_t port);

#endif
