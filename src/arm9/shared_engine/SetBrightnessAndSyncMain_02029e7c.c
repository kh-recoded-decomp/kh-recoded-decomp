#include "nitro/types.h"

extern int data_02060388;
extern int ClampValueByMode_02029e28(int value, int index);
extern void func_02006748(volatile unsigned short *dst, int value);

void SetBrightnessAndSyncMain_02029e7c(int value)
{
    int brightness = ClampValueByMode_02029e28(value, 0);
    *((signed char *)&data_02060388 + 1) = brightness;
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    if (*dispstat & 1) {
        func_02006748(dispstat + 0x34, brightness);
        *(u8 *)&data_02060388 &= 0xfe;
        return;
    }
    *(u8 *)&data_02060388 |= 1;
}
