#include "CppUTest/TestHarness.h"

#include "LightScheduler.h"
#include "FakeTimeService.h"


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