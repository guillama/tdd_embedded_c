#ifndef D_IO_H
#define D_IO_H

#include <stdint.h>

typedef uint32_t ioAdress;
typedef uint16_t ioData;

ioData IO_Read(ioAdress offset);
void IO_Write(ioAdress offset, ioData data);

#endif