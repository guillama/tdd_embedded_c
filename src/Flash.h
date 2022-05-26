#ifndef D_FLASH
#define D_FLASH

#include "IO.h"

typedef enum
{
    CommandRegister = 0x0,
    StatusRegister = 0x0,

} Flash_Registers;

typedef enum
{
    ProgramCommand = 0x40,
    Reset = 0xff,

} Flash_Command;

enum
{
    FLASH_SUCCESS = 0,
    FLASH_VPP_ERROR = 3,
    FLASH_READ_BACK_ERROR = 7,
};

enum
{
    VppErrorBit = 1 << 3,
    ReadyBit = 1 << 7,
};

int Flash_Write(ioAddress address, ioData data);

#endif