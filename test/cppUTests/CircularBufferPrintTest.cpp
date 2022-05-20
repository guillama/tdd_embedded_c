#include "CppUTest/TestHarness.h"
#include "FormatOutputSpy.h"

extern "C"
{
    #include "Utils.h"
    #include "CircularBuffer.h"
}



TEST_GROUP(CircularBufferPrint)
{
    CircularBuffer buffer;
    const char * expectedOutput;
    const char * actualOutput;

    void setup()
    {
        UT_PTR_SET(FormatOutput, FormatOutputSpy);

        FormatOutputSpy_Create(128);
        actualOutput = FormatOutputSpy_GetOutput();
        buffer = CircularBuffer_Create(10);
    }

    void teardown()
    {
        CircularBuffer_Destroy(buffer);
        FormatOutputSpy_Destroy();
    }
};


TEST(CircularBufferPrint, PrintEmpty)
{
    expectedOutput = "Circular buffer content:\n<>\n";

    CircularBuffer_Print(buffer);

    STRCMP_EQUAL(actualOutput, expectedOutput);
}

TEST(CircularBufferPrint, PrintAfterOneIsPut)
{
    expectedOutput = "Circular buffer content:\n<17>\n";

    CircularBuffer_Put(buffer, 17);

    CircularBuffer_Print(buffer);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterSeveralIsPut)
{
    expectedOutput = "Circular buffer content:\n<10, 20, 30>\n";

    CircularBuffer_Put(buffer, 10);
    CircularBuffer_Put(buffer, 20);
    CircularBuffer_Put(buffer, 30);

    CircularBuffer_Print(buffer);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterFullBuffer)
{
    expectedOutput = "Circular buffer content:\n<10, 20, 30, 40, 50>\n";

    CircularBuffer b = CircularBuffer_Create(5);
    CircularBuffer_Put(b, 10);
    CircularBuffer_Put(b, 20);
    CircularBuffer_Put(b, 30);
    CircularBuffer_Put(b, 40);
    CircularBuffer_Put(b, 50);

    CircularBuffer_Print(b);
    CircularBuffer_Destroy(b);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterWrapping)
{
    expectedOutput = "Circular buffer content:\n<20, 30, 40, 50>\n";

    CircularBuffer b = CircularBuffer_Create(5);

    CircularBuffer_Put(b, 10);
    CircularBuffer_Put(b, 20);
    CircularBuffer_Put(b, 30);
    CircularBuffer_Put(b, 40);

    CircularBuffer_Get(b);

    CircularBuffer_Put(b, 50);

    CircularBuffer_Print(b);
    CircularBuffer_Destroy(b);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterWrappingAndFull)
{
    expectedOutput = "Circular buffer content:\n<20, 30, 40, 50, 60>\n";

    CircularBuffer b = CircularBuffer_Create(5);

    CircularBuffer_Put(b, 10);
    CircularBuffer_Put(b, 20);
    CircularBuffer_Put(b, 30);
    CircularBuffer_Put(b, 40);
    CircularBuffer_Put(b, 50);

    CircularBuffer_Get(b);

    CircularBuffer_Put(b, 60);

    CircularBuffer_Print(b);
    CircularBuffer_Destroy(b);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}

TEST(CircularBufferPrint, PrintAfterAddingSeveralValuesInFullBuffer)
{
    expectedOutput = "Circular buffer content:\n<60, 70, 80, 40, 50>\n";

    CircularBuffer b = CircularBuffer_Create(5);

    CircularBuffer_Put(b, 10);
    CircularBuffer_Put(b, 20);
    CircularBuffer_Put(b, 30);
    CircularBuffer_Put(b, 40);
    CircularBuffer_Put(b, 50);
    CircularBuffer_Put(b, 60);
    CircularBuffer_Put(b, 70);
    CircularBuffer_Put(b, 80);

    CircularBuffer_Print(b);
    CircularBuffer_Destroy(b);

    STRCMP_EQUAL(expectedOutput, actualOutput);
}