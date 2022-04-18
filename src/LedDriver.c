#include <stdio.h>
#include <stdint.h>

#include "RuntimeError.h"
#include "LedDriver_helpers.h"

uint16_t * ledsAddress;
uint16_t ledImages;


void LedDriver_Create(uint16_t * address)
{
    ledsAddress = address;
    ledImages = 0;

    updateHardware();
}


void LedDriver_Destroy(void)
{

}


void LedDriver_TurnOn(uint16_t ledNumber)
{
    if (isLedOutOfBounds(ledNumber))
    {
        RUNTIME_ERROR("LED Driver: Out-of-bounds LED", -1);
        return;
    }

    setLedImageBit(ledNumber);

    updateHardware();
}


void LedDriver_TurnOff(uint16_t ledNumber)
{
    if (isLedOutOfBounds(ledNumber)) {
        return;
    }

    clearLedImageBit(ledNumber);

    updateHardware();
}


void LedDriver_TurnAllLedsOn(void)
{
    ledImages = 0xFFFF;

    updateHardware();
}


void LedDriver_TurnAllLedsOff(void)
{
    ledImages = 0;

    updateHardware();
}


int LedDriver_IsOn(uint16_t ledNumber)
{
    if (isLedOutOfBounds(ledNumber))
    {
        return 0;
    }

    return ledImages & (convertLedNumbertoBit(ledNumber));
}


int LedDriver_IsOff(uint16_t ledNumber)
{
    return !(LedDriver_IsOn(ledNumber));
}