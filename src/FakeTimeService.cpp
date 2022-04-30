#include "FakeTimeService.h"

static Time myTime;


void TimeService_GetTime(Time * time)
{
    time-> dayOfWeek = myTime.dayOfWeek;
    time->minutesOfDay = myTime.minutesOfDay;
}


void TimeService_Create()
{
    myTime.dayOfWeek = TIME_UNKNOWN;
    myTime.minutesOfDay = TIME_UNKNOWN;
}

void TimeService_Destroy()
{
    
}


void FakeTimeService_SetDay(int day)
{
    myTime.dayOfWeek = day;
}


void FakeTimeService_SetMinute(int minutes)
{
    myTime.minutesOfDay = minutes;
}