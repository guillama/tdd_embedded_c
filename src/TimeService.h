#ifndef __TIME_SERVICE__
#define __TIME_SERVICE__

typedef struct
{
    int dayOfWeek;
    int minutesOfDay;

} Time;

typedef void (*WakeUpCalllback)(void);

enum
{
    TIME_UNKNOWN = -1,
    MONDAY = 1,
    TUESDAY = 2,
    SATURDAY = 6,

    SUNDAY = 7,
    WEEKEND = 8,
    EVERYDAY = 9,
};

void TimeService_Create();
void TimeService_Destroy();
void TimeService_GetTime(Time * time);

void TimeService_SetPeriodicAlarmInSeconds(int seconds, WakeUpCalllback callback);
void TimeService_CancelPeriodicAlarmInSeconds(int seconds, WakeUpCalllback callback);

#endif