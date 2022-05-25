#include "Flash.h"


int Flash_Write(ioAdress address, ioData data)
{
    IO_Write(0, 0x40);
    IO_Write(address, 0xBEEF);

    IO_Read(0);
    IO_Read(address);

    return 0;
}