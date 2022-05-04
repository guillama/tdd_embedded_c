#include "CppUTest/CommandLineTestRunner.h"
#include "CppUTest/TestHarness.h"

#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"

static void setTimeTo(int day, int minutes);
static void checkLightState(int id, int state);


static void setTimeTo(int day, int minutes)
{
  FakeTimeService_SetDay(day);
  FakeTimeService_SetMinute(minutes);
}


static void checkLightState(int id, int state)
{
  LONGS_EQUAL(id, LightControllerSpy_GetLastId());
  LONGS_EQUAL(state, LightControllerSpy_GetLastState());
}


TEST_GROUP(LightScheduler)
{
  void setup()
  {
    LightController_Create();
    LightScheduler_Create();
  }

  void teardown()
  {
    LightController_Destroy();
    LightScheduler_Destroy();
  }
};


TEST(LightScheduler, FirstTest)
{
   checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, NoScheduleNothingHappens)
{
  setTimeTo(MONDAY, 180);

  LightScheduler_WakeUp();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, ScheduleOnEveryDayNoTimeYet)
{
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

  setTimeTo(MONDAY, 1199);

  LightScheduler_WakeUp();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, ScheduleOnEverydayItsTime)
{
  LightScheduler_ScheduleTurnOn(3, EVERYDAY, 1200);

  setTimeTo(MONDAY, 1200);

  LightScheduler_WakeUp();

  checkLightState(3, LIGHT_ON);
}


TEST(LightScheduler, ScheduleOffEverydayItsTime)
{
  LightScheduler_ScheduleTurnOff(5, EVERYDAY, 1500);

  setTimeTo(MONDAY, 1500);

  LightScheduler_WakeUp();

  checkLightState(5, LIGHT_OFF);
}


TEST(LightScheduler, ScheduleTuesdayButItsMonday)
{
  LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000);

  setTimeTo(MONDAY, 1000);

  LightScheduler_WakeUp();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, ScheduleTuesdayAnItsTuesday)
{
  LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000);

  setTimeTo(TUESDAY, 1000);

  LightScheduler_WakeUp();

  checkLightState(1, LIGHT_ON);
}


TEST(LightScheduler, ScheduleWeekendButItsMonday)
{
  LightScheduler_ScheduleTurnOn(1, WEEKEND, 1000);

  setTimeTo(MONDAY, 1000);

  LightScheduler_WakeUp();

  checkLightState(LIGHT_ID_UNKNOWN, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, ScheduleWeekendAnItsSaturday)
{
  LightScheduler_ScheduleTurnOn(1, WEEKEND, 1000);

  setTimeTo(SATURDAY, 1000);

  LightScheduler_WakeUp();

  checkLightState(1, LIGHT_ON);
}


TEST(LightScheduler, ScheduleWeekendAnItsSunday)
{
  LightScheduler_ScheduleTurnOn(1, WEEKEND, 1000);

  setTimeTo(SUNDAY, 1000);

  LightScheduler_WakeUp();

  checkLightState(1, LIGHT_ON);
}


TEST_GROUP(LightSchedulerInitAndCleanup)
{

};


TEST(LightSchedulerInitAndCleanup, DestroyCancelsOneMinuteAlarm)
{
  LightScheduler_Create();
  LightScheduler_Destroy();
  POINTERS_EQUAL(NULL, (void *)FakeTimeService_GetAlarmCallback());
}


TEST(LightSchedulerInitAndCleanup, CreateStartsOneMinuteAlarm)
{
  LightScheduler_Create();
  POINTERS_EQUAL( (void *)LightScheduler_WakeUp,
                  (void *)FakeTimeService_GetAlarmCallback());

  LONGS_EQUAL(60, FakeTimeService_GetAlarmPeriod());
  LightScheduler_Destroy();
}