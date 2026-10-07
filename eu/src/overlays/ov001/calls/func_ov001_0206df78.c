#include "nitro/types.h"

extern int func_ov001_02068084(void);
extern void SetSessionFlag(u32 flag);
extern void AddSessionCounter(int category, int amount);
extern u32 ReadSessionPackedBits(u32 category, u32 index);
extern void WriteSessionPackedBits(u32 category, u32 index, u32 value);

void func_ov001_0206df78(void)
{
    int flagSet;
    u32 count;

    flagSet = func_ov001_02068084();
    if (flagSet == 0) {
        SetSessionFlag(0x3707);
    }
    AddSessionCounter(6, 1);
    count = ReadSessionPackedBits(0xb26, 0x11);
    if (count < 99999) {
        WriteSessionPackedBits(0xb26, 0x11, count + 1);
    }
}
