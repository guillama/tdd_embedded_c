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


static LightScheduleEvent scheduleEvent[MAX_SCHEDULE];

static int schedule(int id, int day, int minutes, int event);
static void processEventDueNow(LightScheduleEvent * event);
static void operateLight(LightScheduleEvent * lightEvent);

static int itsTime(const LightScheduleEvent * const event);
static int isScheduledToday(int scheduledDay, int today);


void LightScheduler_Create(void)
{
    for(int i = 0; i < MAX_SCHEDULE; i++)
        scheduleEvent[i].id = -1;

    TimeService_SetPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}


void LightScheduler_Destroy(void)
{
    TimeService_CancelPeriodicAlarmInSeconds(60, LightScheduler_WakeUp);
}


void LightScheduler_WakeUp(void)
{
    for(int i = 0; i < MAX_SCHEDULE; i++)
    {
        processEventDueNow(&scheduleEvent[i]);
    }
    
}


static void processEventDueNow(LightScheduleEvent * event)
{
    if (! itsTime(event))
        return;

    if (event->id == -1)
        return;

    operateLight(event);
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


static void operateLight(LightScheduleEvent * lightEvent)
{
    if (lightEvent->event == TURN_ON)
        LightController_On(lightEvent->id);
    else if (lightEvent->event == TURN_OFF)
        LightController_Off(lightEvent->id);
}


int LightScheduler_ScheduleTurnOn(int id, int day, int minutes)
{
    return schedule(id, day, minutes, TURN_ON);
}


int LightScheduler_ScheduleTurnOff(int id, int day, int minutes)
{
    return schedule(id, day, minutes, TURN_OFF);
}


static int schedule(int id, int day, int minutes, int event)
{
    if (id < 0 || id > 31)
        return LS_LIGHT_OUT_OF_BOUNDS;

    for (int i = 0; i < MAX_SCHEDULE; i++)
    {
        if (scheduleEvent[i].id != -1)
            continue;

        scheduleEvent[i].minutesOfDay = minutes;
        scheduleEvent[i].dayOfWeek = day;
        scheduleEvent[i].event = event;
        scheduleEvent[i].id = id;

        return LS_OK;
    }
    
    return LS_TOO_MANY_EVENTS;
}


void LightScheduler_ScheduleRemove(int id, int day, int minutes)
{
    for (int i = 0; i < MAX_SCHEDULE; i++)
    {
        if (scheduleEvent[i].id == id
        && scheduleEvent[i].dayOfWeek == day
        && scheduleEvent[i].minutesOfDay == minutes)
        {
            scheduleEvent[i].id = -1;

            LightController_Remove(id);
            return;
        }
    }
}

