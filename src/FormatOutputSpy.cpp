#include "FormatOutputSpy.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

static int message_len;
static char * message;

static int message_offset;
static int message_used;

void FormatOutputSpy_Create(int length)
{
    message_len = length + 1;

    message = (char *)calloc(message_len + 1, sizeof(char));

    message_offset = 0;
    message_used = 0;
}

void FormatOutputSpy_Destroy()
{
    free(message);
}

char * FormatOutputSpy_GetOutput()
{
    return message;
}

int FormatOutputSpy(const char * format, ...)
{
    int written_size;
    va_list args;

    va_start(args, format);

    written_size = vsnprintf(  message + message_offset, 
                                message_len - message_used, 
                                format, 
                                args);

    message_offset += written_size;
    message_used += written_size;

    va_end(args);

    //strncat(message, format, message_len - strlen(message));

    return 1;
}