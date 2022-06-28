#ifndef __FORMAT_OUTPUT_SPY_H__
#define __FORMAT_OUTPUT_SPY_H__

void FormatOutputSpy_Create(int length);
void FormatOutputSpy_Destroy();

char * FormatOutputSpy_GetOutput();
int FormatOutputSpy(const char * msg, ...);

#endif