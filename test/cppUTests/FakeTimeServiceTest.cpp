#include "CppUTest/TestHarness.h"
#include "CppUTest/CommandLineTestRunner.h"

#include "TimeService.h"
#include "FakeTimeService.h"


TEST_GROUP(FakeTimeService)
{
    void setup()
    {
        TimeService_Create();
    }

    void teardown()
    {
        TimeService_Destroy();
    }
};


TEST(FakeTimeService, Create)
{
    Time time;

    TimeService_GetTime(&time);

    LONGS_EQUAL(TIME_UNKNOWN, time.dayOfWeek);
    LONGS_EQUAL(TIME_UNKNOWN, time.minutesOfDay);
}


TEST(FakeTimeService, Set)
{
    Time time;

    FakeTimeService_SetDay(MONDAY);
    FakeTimeService_SetMinute(42);

    TimeService_GetTime(&time);

    LONGS_EQUAL(MONDAY, time.dayOfWeek);
    LONGS_EQUAL(42, time.minutesOfDay);
}


TEST(FakeTimeService, SetPeriodicAlarm)
{
    TimeService_SetPeriodicAlarmInSeconds(30, TimeService_Create);

    POINTERS_EQUAL((void *)TimeService_Create, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(30, FakeTimeService_GetAlarmPeriod());
}


TEST(FakeTimeService, CancelPeriodicAlarmButBadPeriod)
{
    TimeService_SetPeriodicAlarmInSeconds(30, TimeService_Create);
    TimeService_CancelPeriodicAlarmInSeconds(60, TimeService_Create);

    POINTERS_EQUAL((void *)TimeService_Create, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(30, FakeTimeService_GetAlarmPeriod());
}


TEST(FakeTimeService, CancelPeriodicAlarmButBadCallback)
{
    TimeService_SetPeriodicAlarmInSeconds(30, TimeService_Create);
    TimeService_CancelPeriodicAlarmInSeconds(30, NULL);

    POINTERS_EQUAL((void *)TimeService_Create, (void *)FakeTimeService_GetAlarmCallback());
    LONGS_EQUAL(30, FakeTimeService_GetAlarmPeriod());
}

