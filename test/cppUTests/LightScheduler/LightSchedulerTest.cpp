#include "CppUTest/TestHarness.h"

#include "LightScheduler.h"
#include "LightControllerSpy.h"
#include "FakeTimeService.h"


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

  void setTimeTo(int day, int minutes)
  {
    FakeTimeService_SetDay(day);
    FakeTimeService_SetMinute(minutes);
  }


  void checkLightState(int id, int state)
  {
    if (id == LIGHT_ID_UNKNOWN)
    {
      LONGS_EQUAL(id, LightControllerSpy_GetLastId());
      LONGS_EQUAL(state, LightControllerSpy_GetLastState());
    }
    else
      LONGS_EQUAL(state, LightControllerSpy_GetLightState(id));
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


TEST(LightScheduler, ScheduleTwoEventsAttheSameTime)
{
  LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000);
  LightScheduler_ScheduleTurnOn(2, TUESDAY, 1000);

  setTimeTo(TUESDAY, 1000);

  LightScheduler_WakeUp();

  checkLightState(1, LIGHT_ON);
  checkLightState(2, LIGHT_ON);
}


TEST(LightScheduler, RejectsTooManyEvents)
{
  for (int i = 0; i < MAX_SCHEDULE; i++)
  {
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000 + i));
  }

  LONGS_EQUAL(LS_TOO_MANY_EVENTS, LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000 + 129));
}


TEST(LightScheduler, RemoveRecycleSlot)
{
  for (int i = 0; i < MAX_SCHEDULE; i++)
  {
    LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000 + i));
  }

  LightScheduler_ScheduleRemove(1, TUESDAY, 1000);

  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(1, TUESDAY, 1000 + 129));
}


TEST(LightScheduler, RemoveMultipleScheduledEvent)
{
  LightScheduler_ScheduleTurnOn(6, MONDAY, 1200);
  LightScheduler_ScheduleTurnOn(7, MONDAY, 1200);
  LightScheduler_ScheduleRemove(7, MONDAY, 1200);

  setTimeTo(MONDAY, 1200);

  LightScheduler_WakeUp();

  checkLightState(6, LIGHT_ON);
  checkLightState(7, LIGHT_STATE_UNKNOWN);
}


TEST(LightScheduler, AcceptsValidLightIds)
{
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(0, MONDAY, 600));
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(15, MONDAY, 600));
  LONGS_EQUAL(LS_OK, LightScheduler_ScheduleTurnOn(31, MONDAY, 600));
}


TEST(LightScheduler, RejectsInvalidLightIds)
{
  LONGS_EQUAL(LS_LIGHT_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(-1, MONDAY, 600));
  LONGS_EQUAL(LS_LIGHT_OUT_OF_BOUNDS, LightScheduler_ScheduleTurnOn(32, MONDAY, 600));
}
