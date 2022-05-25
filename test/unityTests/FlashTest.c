#include "unity.h"
#include "MockIO.h"

#include "Flash.h"

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
    IO_Read_ExpectAndReturn(StatusRegister, 1 << 7);
    IO_Read_ExpectAndReturn(address, data);

    result = Flash_Write(address, data);

    TEST_ASSERT_EQUAL_INT32(FLASH_SUCCESS, result);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_WriteSucceedsAndReadyImmediatly);

    return UNITY_END();
}