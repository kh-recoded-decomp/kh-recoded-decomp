#include "nitro/types.h"

extern int data_02060388;
extern int ClampValueByMode_02029e28(int value, int index);
extern void func_02006748(volatile unsigned short *dst, int value);

void SetSecondaryBrightness_02029ed0(int value)
{
    int brightness = ClampValueByMode_02029e28(value, 1);
    *((signed char *)&data_02060388 + 2) = brightness;
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    if (*dispstat & 1) {
        func_02006748((volatile unsigned short *)0x0400106c, brightness);
        *(u8 *)&data_02060388 &= 0xfd;
        return;
    }
    *(u8 *)&data_02060388 |= 2;
}
