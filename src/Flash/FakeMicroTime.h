#ifndef D_FAKE_MICRO_TIME
#define D_FAKE_MICRO_TIME

#include <stdint.h>

void FakeMicroTime_Create(int start, int incr);

uint32_t MicroTime_Get();

#endif