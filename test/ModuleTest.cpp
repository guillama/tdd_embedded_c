#include "CppUTest/CommandLineTestRunner.h"


TEST_GROUP(FirstTestGroup)
{
};

TEST(FirstTestGroup, FirstTest)
{
   FAIL("Fail me!");
}

int main(int ac, char** av)
{
  return RUN_ALL_TESTS(ac, av);
}