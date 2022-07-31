#include <stdint.h>

#include "unity.h"
#include "LedDriver.h"

#include "mocks/RuntimeErrorStub.h"


static uint16_t virtualLeds = 0xffff;


void setUp (void) 
{
    LedDriver_Create(&virtualLeds);
}


void tearDown (void) 
{
    LedDriver_Destroy();
}


void test_LedsOffAfterInit()
{
    TEST_ASSERT_EQUAL_UINT16(0, virtualLeds);
}


void test_TurnOnOneLed()
{
    LedDriver_TurnOn(1);

    TEST_ASSERT_EQUAL_UINT16(1, virtualLeds);
}


void test_TurnOffLedOne()
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOff(1);

    TEST_ASSERT_EQUAL_UINT16(0, virtualLeds);
}


void test_TurnOnMultipleLeds()
{
    LedDriver_TurnOn(8);
    LedDriver_TurnOn(9);

    TEST_ASSERT_EQUAL_HEX16(0x180, virtualLeds);
}


void test_TurnOffMultipleLeds()
{
    LedDriver_TurnAllLedsOn();
    LedDriver_TurnOff(8);
    LedDriver_TurnOff(9);

    TEST_ASSERT_EQUAL_HEX16(~0x180 & 0xFFFF, virtualLeds);
}


void test_TurnAllLedsOn()
{
    LedDriver_TurnAllLedsOn();

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}


void test_TurnAllLedsOff()
{
    LedDriver_TurnAllLedsOn();
    LedDriver_TurnAllLedsOff();

    TEST_ASSERT_EQUAL_HEX16(0, virtualLeds);
}


void test_LedMemoryIsNotReadable()
{
    virtualLeds = 0xFFFF;

    LedDriver_TurnOn(1);

    TEST_ASSERT_EQUAL_HEX16(0x0001, virtualLeds);
}


void test_UpperAndLowerBounds()
{
    LedDriver_TurnOn(1);
    LedDriver_TurnOn(16);

    TEST_ASSERT_EQUAL_HEX16(0x8001, virtualLeds);
}


void test_TurnOnOutOfBoundsLedsChangeNothing()
{
    LedDriver_TurnOn(-1);
    LedDriver_TurnOn(0);
    LedDriver_TurnOn(17);
    LedDriver_TurnOn(34);

    TEST_ASSERT_EQUAL_HEX16(0x0, virtualLeds);
}


void test_TurnOffOutOfBoundsLedsChangeNothing()
{
    LedDriver_TurnAllLedsOn();

    LedDriver_TurnOff(-1);
    LedDriver_TurnOff(0);
    LedDriver_TurnOff(17);
    LedDriver_TurnOff(34);

    TEST_ASSERT_EQUAL_HEX16(0xFFFF, virtualLeds);
}


void test_OutOfBoundsProduceRuntimeError()
{
    LedDriver_TurnOn(-1);

    TEST_ASSERT_EQUAL_STRING("LED Driver: Out-of-bounds LED", RuntimeErrorStub_GetLastError());
    TEST_ASSERT_EQUAL_INT(-1, RuntimeErrorStub_GetLastParameter());
}


void test_IsLedOn()
{
    TEST_ASSERT_FALSE(LedDriver_IsOn(11));

    LedDriver_TurnOn(11);

    TEST_ASSERT_TRUE(LedDriver_IsOn(11));
}


void test_IsLedOff()
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(11));

    LedDriver_TurnOn(11);

    TEST_ASSERT_FALSE(LedDriver_IsOff(11));
}


void test_OutOfBoundsToDo()
{
    TEST_IGNORE();
}


void test_OuOfBoundsLedsAreAlwaysOff()
{
    TEST_ASSERT_TRUE(LedDriver_IsOff(0));
    TEST_ASSERT_TRUE(LedDriver_IsOff(17));
    TEST_ASSERT_TRUE(LedDriver_IsOff(65535));

    TEST_ASSERT_FALSE(LedDriver_IsOn(0));
    TEST_ASSERT_FALSE(LedDriver_IsOn(17));
    TEST_ASSERT_FALSE(LedDriver_IsOn(65535));
}


int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_LedsOffAfterInit);
    RUN_TEST(test_TurnOnOneLed);
    RUN_TEST(test_TurnOffLedOne);
    RUN_TEST(test_TurnOnMultipleLeds);
    RUN_TEST(test_TurnOffMultipleLeds);
    RUN_TEST(test_TurnAllLedsOn);
    RUN_TEST(test_TurnAllLedsOff);
    RUN_TEST(test_LedMemoryIsNotReadable);
    RUN_TEST(test_UpperAndLowerBounds);
    RUN_TEST(test_TurnOnOutOfBoundsLedsChangeNothing);
    RUN_TEST(test_TurnOffOutOfBoundsLedsChangeNothing);
    RUN_TEST(test_OutOfBoundsProduceRuntimeError);
    RUN_TEST(test_IsLedOn);
    RUN_TEST(test_IsLedOff);
    RUN_TEST(test_OuOfBoundsLedsAreAlwaysOff);

    RUN_TEST(test_OutOfBoundsToDo);

    return UNITY_END();
}