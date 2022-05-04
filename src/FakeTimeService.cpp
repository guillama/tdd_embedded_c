#include <stdlib.h>

#include "FakeTimeService.h"

static Time myTime;
static WakeUpCalllback wakeUpCallback;
static int period;


void TimeService_Create()
{
    myTime.dayOfWeek = TIME_UNKNOWN;
    myTime.minutesOfDay = TIME_UNKNOWN;
}

void TimeService_Destroy()
{
    
}

void TimeService_GetTime(Time * time)
{
    time-> dayOfWeek = myTime.dayOfWeek;
    time->minutesOfDay = myTime.minutesOfDay;
}

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCalllback callback)
{
    wakeUpCallback = callback;
    period = seconds;

}

void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCalllback callback)
{
    if (seconds == period && callback == wakeUpCallback)
    {
        wakeUpCallback = NULL;
        period = 0;
    }
}


void FakeTimeService_SetDay(int day)
{
    myTime.dayOfWeek = day;
}


void FakeTimeService_SetMinute(int minutes)
{
    myTime.minutesOfDay = minutes;
}


WakeUpCalllback FakeTimeService_GetAlarmCallback()
{
    return wakeUpCallback;
}

int FakeTimeService_GetAlarmPeriod()
{
    return period;
}