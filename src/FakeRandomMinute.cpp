#include "FakeRandomMinute.h"

static int randomStart;
static int randomStep;

void FakeRandomMinute_SetFirstAndIncrement(int start, int step)
{
    randomStart = start;
    randomStep = step;
}

int FakeRandomMinute_Get()
{
    return randomStart;
}