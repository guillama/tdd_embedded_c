#ifndef __LIGHT_SCHEDULER__
#define __LIGHT_SCHEDULER__

enum
{
    TURN_ON,
    TURN_OFF,
};

enum
{
    LS_OK,
    LS_TOO_MANY_EVENTS,
    LS_LIGHT_OUT_OF_BOUNDS,
};

void LightScheduler_Create();
void LightScheduler_Destroy();

void LightController_Remove(int id);
void LightScheduler_WakeUp();

int LightScheduler_ScheduleTurnOn(int id, int day, int minute);
int LightScheduler_ScheduleTurnOff(int id, int day, int minutes);

void LightScheduler_ScheduleRemove(int id, int day, int minutes);

#endif