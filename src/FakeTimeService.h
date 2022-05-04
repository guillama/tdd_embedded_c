#ifndef __FAKE_TIME_SERVICE__
#define __FAKE_TIME_SERVICE__

#include "TimeService.h"

void FakeTimeService_SetDay(int day);
void FakeTimeService_SetMinute(int minutes);

WakeUpCalllback FakeTimeService_GetAlarmCallback();
int FakeTimeService_GetAlarmPeriod();

#endif