#ifndef __LIGHT_SCHEDULER__
#define __LIGHT_SCHEDULER__

enum
{
    TURN_ON,
    TURN_OFF,
};

void LightScheduler_Create();
void LightScheduler_Destroy();

void LightScheduler_WakeUp();
void LightScheduler_ScheduleTurnOn(int id, int day, int minute);
void LightScheduler_ScheduleTurnOff(int id, int day, int minutes);

#endif