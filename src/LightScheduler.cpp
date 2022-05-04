#include "LightScheduler.h"
#include "LightController.h"
#include "TimeService.h"

typedef struct 
{
    int id;
    int dayOfWeek;
    int minutesOfDay;
    int event;

} LightScheduleEvent;


static LightScheduleEvent scheduleEvent;

static void schedule(int id, int day, int minutes, int event);
static void processEventDueNow(LightScheduleEvent * event);
static void operateLight(LightScheduleEvent * lightEvent);

static int itsTime(const LightScheduleEvent * const event);
static int isScheduledToday(int scheduledDay, int today);


void LightScheduler_Create(void)
{
    scheduleEvent.id = -1;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}


void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}


void LightScheduler_WakeUp(void)
{
    if (! itsTime(&scheduleEvent))
        return;

    processEventDueNow(&scheduleEvent);
}


static int itsTime(const LightScheduleEvent * const event)
{
    Time time;

    TimeService_GetTime(&time);

    if (time.minutesOfDay != event->minutesOfDay)
        return 0;

    if (!isScheduledToday(event->dayOfWeek, time.dayOfWeek))
        return 0;

    return 1;
}


static int isScheduledToday(int scheduledDay, int today)
{
    if (scheduledDay == EVERYDAY)
        return 1;

    if (scheduledDay == WEEKEND
    && (today == SATURDAY || today == SUNDAY))
        return 1;

    if (scheduledDay == today)
        return 1;

    return 0;
}


static void processEventDueNow(LightScheduleEvent * event)
{
    if (event->id == -1)
        return;

    operateLight(event);
}


static void operateLight(LightScheduleEvent * lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}


void LightScheduler_ScheduleTurnOn(int id, int day, int minutes)
{
    schedule(id, day, minutes, TURN_ON);
}


void LightScheduler_ScheduleTurnOff(int id, int day, int minutes)
{
    schedule(id, day, minutes, TURN_OFF);
}


static void schedule(int id, int day, int minutes, int event)
{
    scheduleEvent.minutesOfDay = minutes;
    scheduleEvent.dayOfWeek = day;
    scheduleEvent.event = event;
    scheduleEvent.id = id;
}