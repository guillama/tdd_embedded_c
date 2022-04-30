#include "LightControllerSpy.h"

static int lightId;
static int lightState;

void LightController_Create(void)
{
    lightId = LIGHT_ID_UNKNOWN;
    lightState = LIGHT_STATE_UNKNOWN;
}

void LightController_Destroy(void)
{
    
}

void LightController_On(int id)
{
    lightId = 10;
    lightState = LIGHT_ON;
}

int LightControllerSpy_GetLastId(void)
{
    return lightId;
}

int LightControllerSpy_GetLastState(void)
{
    return lightState;
}

