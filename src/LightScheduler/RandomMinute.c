#include <stdlib.h>

#include "RandomMinute.h"

static int myBound;

void RandomMinute_Create(int bound)
{
    myBound = bound;
}

int RandomMinute_GetImpl()
{
    return myBound - rand() % (myBound * 2 + 1);
}

int (*RandomMinute_Get)(void) = RandomMinute_GetImpl;