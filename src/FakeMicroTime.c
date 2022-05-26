#include "FakeMicroTime.h"

static int time;
static int increment;
static int totalDelay;

void FakeMicroTime_Create(int start, int incr)
{
    time = start;
    increment = incr;
    totalDelay = 0;
}

uint32_t MicroTime_Get()
{
    uint32_t t = time;

    time += increment;

    return t;
}