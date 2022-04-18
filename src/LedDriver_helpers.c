#include "LedDriver_helpers.h"


extern int16_t * ledsAddress;
extern uint16_t ledImages;


void clearLedImageBit(uint16_t ledNumber)
{
    ledImages &= ~(convertLedNumbertoBit(ledNumber));
}


int isLedOutOfBounds(uint16_t ledNumber)
{
    return (ledNumber < 1 || ledNumber > 16);
}


void setLedImageBit(uint16_t ledNumber)
{
    ledImages |= convertLedNumbertoBit(ledNumber);
}


uint16_t convertLedNumbertoBit(uint16_t ledNumber)
{
    return 1 << (ledNumber - 1);
}


void updateHardware(void)
{
    *ledsAddress = ledImages;
}