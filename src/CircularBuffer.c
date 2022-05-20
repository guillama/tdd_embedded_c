#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "CircularBuffer.h"
#include "Utils.h"


CircularBuffer CircularBuffer_Create(int size)
{
    CircularBuffer buffer = malloc(sizeof(_CircularBuffer));

    buffer->values = malloc(size * sizeof(int));

    buffer->size = size;
    buffer->inIndex = 0;
    buffer->outIndex = 0;

    return buffer;
}

void CircularBuffer_Destroy(CircularBuffer buffer)
{
    free(buffer->values);
    free(buffer);
}

void CircularBuffer_Print(CircularBuffer buffer)
{
    int i = 0;

    int nval = buffer->inIndex - buffer->outIndex;

    if (nval > buffer->size)
        nval = buffer->size;

    FormatOutput("Circular buffer content:\n<");

    if (nval > 0)
        FormatOutput("%d", buffer->values[buffer->outIndex]);

    printf("start: %d, end: %d", buffer->outIndex, nval + buffer->outIndex);


    for (i = buffer->outIndex + 1; i < nval + buffer->outIndex; i++)
    {
        int index = i % buffer->size;
        FormatOutput(", %d", buffer->values[index]);
    }

    FormatOutput(">\n");
}

void CircularBuffer_Put(CircularBuffer buffer, int val)
{
    int index = buffer->inIndex % buffer->size;

    printf("index %d\n", index);

    buffer->values[index] = val;
    buffer->inIndex++;
}

int CircularBuffer_Get(CircularBuffer buffer)
{
    int output = buffer->values[buffer->outIndex];

    buffer->outIndex++;

    return output;
}
