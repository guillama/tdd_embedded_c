#ifndef __CIRCULAR_BUFFER__
#define __CIRCULAR_BUFFER__

typedef struct
{
    int * values;
    int size;
    int inIndex;
    int outIndex;

} _CircularBuffer;

typedef _CircularBuffer *CircularBuffer;

CircularBuffer CircularBuffer_Create(int size);
void CircularBuffer_Destroy(CircularBuffer buffer);

void CircularBuffer_Put(CircularBuffer buffer, int val);
int CircularBuffer_Get(CircularBuffer buffer);
void CircularBuffer_Print(CircularBuffer buffer);

#endif