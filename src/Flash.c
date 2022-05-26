#include "Flash.h"


int Flash_Write(ioAddress address, ioData data)
{
    ioData status = 0;
    ioData dataBack = 0;

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);

    while ((status & ReadyBit) == 0)
    {
        status = IO_Read(StatusRegister);
    }
        
    if (status & VppErrorBit) {
        IO_Write(StatusRegister, Reset);
        return FLASH_VPP_ERROR;
    }
        

    dataBack = IO_Read(address);

    if (dataBack != data)
        return FLASH_READ_BACK_ERROR;

    return FLASH_SUCCESS;
}