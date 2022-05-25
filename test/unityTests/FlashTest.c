#include "unity.h"
#include "MockIO.h"

#include "Flash.h"

int result = 0;


void setUp()
{
    result = -1;
    
    MockIO_Init();
}

void tearDown()
{
    MockIO_Verify();
    MockIO_Destroy();
}

void test_WriteSucceeds_ReadyImmediatly()
{
    IO_Write_Expect(0, 0x40);
    IO_Write_Expect(0x1000, 0xBEEF);
    IO_Read_ExpectAndReturn(0, 1 << 7);
    IO_Read_ExpectAndReturn(0x1000, 0xBEEF);

    result = Flash_Write(0x1000, 0xBEEF);

    TEST_ASSERT_EQUAL_INT32(0, result);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_WriteSucceeds_ReadyImmediatly);

    return UNITY_END();
}