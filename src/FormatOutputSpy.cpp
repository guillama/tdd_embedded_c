#include "FormatOutputSpy.h"

#include <string.h>
#include <stdlib.h>

static int myLength;
static char * message;

void FormatOutputSpy_Create(int length)
{
    myLength = length;

    message = (char *)calloc(myLength + 1, sizeof(char));
}

void FormatOutputSpy_Destroy()
{
    free(message);
}

char * FormatOutputSpy_GetOutput()
{
    return message;
}

int FormatOutputSpy(const char * msg, ...)
{
    strncat(message, msg, myLength - strlen(message));

    return 1;
}