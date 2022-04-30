#include "CppUTest/CommandLineTestRunner.h"


TEST_GROUP(LightScheduler)
{
};

TEST(LightScheduler, FirstTest)
{
   LONGS_EQUAL(LIGHT_ID_UNKNOWN, LightControllerSpy_GetLastId());
   LONGS_EQUAL(LIGHT_STATE_UNKNOWN, LightControllerSpy_GetLastState());
}

int main(int ac, char** av)
{
  return RUN_ALL_TESTS(ac, av);
}