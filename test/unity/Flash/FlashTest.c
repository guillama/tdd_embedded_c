#include "unity.h"
#include "MockIO.h"

#include "Flash.h"
#include "FakeMicroTime.h"

int result = 0;
ioAddress address;
ioData data;

void setUp()
{
    result = -1;
    address = 0x1000;
    data = 0xBEEF;

    MockIO_Init();
}

void tearDown()
{
    MockIO_Verify();
    MockIO_Destroy();
}

void test_WriteSucceedsAndReadyImmediatly()
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(address, data);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(address, data);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT(FLASH_SUCCESS, result);
}

void test_WriteSucceedsButNotImmediatelyReady()
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(address, data);

    IO_Read_ExpectAndReturn(StatusRegister, 0);
    IO_Read_ExpectAndReturn(StatusRegister, 0);
    IO_Read_ExpectAndReturn(StatusRegister, 0);

    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(address, data);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT(FLASH_SUCCESS, result);
}

void test_WriteFailsBecauseVppError()
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(address, data);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit | VppErrorBit);
    IO_Write_Expect(CommandRegister, Reset);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT(FLASH_VPP_ERROR, result);
}

void test_WriteFailedBecauseReadBackError()
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(address, data);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(address, data-1);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT(FLASH_READ_BACK_ERROR, result);
}

void test_WritesucceedsIgnoreOtherBitsUntilReady()
{
    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(address, data);

    IO_Read_ExpectAndReturn(StatusRegister, ~ReadyBit);
    IO_Read_ExpectAndReturn(StatusRegister, ReadyBit);
    IO_Read_ExpectAndReturn(address, data-1);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT(FLASH_READ_BACK_ERROR, result);
}

void test_WriteFailedBecauseOfTimeout()
{
    int i = 0;

    FakeMicroTime_Create(0, 500);

    IO_Write_Expect(CommandRegister, ProgramCommand);
    IO_Write_Expect(address, data);

    for(i = 0; i < 10; i++)
        IO_Read_ExpectAndReturn(StatusRegister, ~ReadyBit);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT(FLASH_TIMEOUT_ERROR, result);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_WriteSucceedsAndReadyImmediatly);
    RUN_TEST(test_WriteSucceedsButNotImmediatelyReady);
    RUN_TEST(test_WriteFailsBecauseVppError);
    RUN_TEST(test_WriteFailedBecauseReadBackError);
    RUN_TEST(test_WritesucceedsIgnoreOtherBitsUntilReady);
    RUN_TEST(test_WriteFailedBecauseOfTimeout);

    return UNITY_END();
}