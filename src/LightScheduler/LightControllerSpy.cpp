#include "LightControllerSpy.h"

static int lastLightId;
static int lastLightState;
static int lightState[MAX_SCHEDULE];

void LightController_Create(void)
{
    lastLightId = LIGHT_ID_UNKNOWN;
    lastLightState = LIGHT_STATE_UNKNOWN;

    for(int i; i < MAX_SCHEDULE; i++)
        lightState[i] = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
    
}

void LightController_On(int id)
{
    lastLightId = id;
    lastLightState = LIGHT_ON;

    lightState[id] = LIGHT_ON;
}

void LightController_Off(int id)
{
    lastLightId = id;
    lastLightState = LIGHT_OFF;

    lightState[id] = LIGHT_OFF;
}

void LightController_Remove(int id)
{
    lightState[id] = LIGHT_STATE_UNKNOWN;
}

int LightControllerSpy_GetLastId(void)
{
    return lastLightId;
}

int LightControllerSpy_GetLastState(void)
{
    return lastLightState;
}

int LightControllerSpy_GetLightState(int id)
{
    return lightState[id];
}
