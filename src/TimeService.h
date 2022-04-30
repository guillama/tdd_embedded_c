#ifndef __TIME_SERVICE__
#define __TIME_SERVICE__

typedef struct
{
    int dayOfWeek;
    int minutesOfDay;

} Time;

enum
{
    TIME_UNKNOWN = -1,
    MONDAY = 1,
};

void TimeService_Create();
void TimeService_Destroy();
void TimeService_GetTime(Time * time);

#endif