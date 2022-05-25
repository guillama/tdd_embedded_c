#include "IO.h"


int IO_Write(ioAdress addr, ioData data)
{
    ioData * p = 0;
    *(p + addr) = data;
}

ioData IO_Read(ioAdress addr)
{
    ioData * p;
    return *(addr + p);
}