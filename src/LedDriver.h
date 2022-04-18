#ifndef __LED_DRIVER__
#define __LED_DRIVER__


void LedDriver_Create(uint16_t * address);
void LedDriver_Destroy(void);

void LedDriver_TurnOn(uint16_t led);
void LedDriver_TurnOff(uint16_t ledNumber);

void LedDriver_TurnAllLedsOn(void);
void LedDriver_TurnAllLedsOff(void);

int LedDriver_IsOn(uint16_t ledNumber);
int LedDriver_IsOff(uint16_t ledNumber);

#endif