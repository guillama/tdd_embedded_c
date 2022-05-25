#include "IO.h"


int IO_Write(ioAddress addr, ioData data)
{
    ioData * p = 0;
    *(p + addr) = data;
}

ioData IO_Read(ioAddress addr)
{
    ioData * p;
    return *(addr + p);
}