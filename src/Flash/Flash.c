#include "Flash.h"
#include "FakeMicroTime.h"

int Flash_Write(ioAddress address, ioData data)
{
    ioData status = 0;
    uint32_t timestamp = MicroTime_Get();

    IO_Write(CommandRegister, ProgramCommand);
    IO_Write(address, data);

    while ((status & ReadyBit) == 0)
    {
        if ((MicroTime_Get() - timestamp) > FLASH_WRITE_TIMEOUT_US)
            return FLASH_TIMEOUT_ERROR;

        status = IO_Read(StatusRegister);
    }
        
    if (status & VppErrorBit) 
    {
        IO_Write(StatusRegister, Reset);
        return FLASH_VPP_ERROR;
    }

    if (IO_Read(address) != data)
        return FLASH_READ_BACK_ERROR;

    return FLASH_SUCCESS;
}