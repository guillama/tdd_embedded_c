#ifndef __LED_DRIVER_HELPERS__
#define  __LED_DRIVER_HELPERS__

#include <stdint.h>

int isLedOutOfBounds(uint16_t ledNumber);
void setLedImageBit(uint16_t ledNumber);
void clearLedImageBit(uint16_t ledNumber);
uint16_t convertLedNumbertoBit(uint16_t ledNumber);
void updateHardware(void);

#endif