#include "nitro/types.h"

#pragma explicit_zero_data on

extern u8 data_ov001_0209ddd0[];
extern u8 data_ov001_0209ddd7[];
extern void DrawShortLayoutRow_020737fc(void);
extern void func_ov001_02073894(void);

void *data_ov001_0209edf4[14] = {
    NULL,
    (void *)0x0000006E,
    (void *)0x00000005,
    (void *)0x00000001,
    (void *)data_ov001_0209ddd0,
    (void *)0x00000008,
    (void *)DrawShortLayoutRow_020737fc,
    NULL,
    (void *)0x00000030,
    (void *)0x00000004,
    (void *)0x00000003,
    (void *)data_ov001_0209ddd7,
    (void *)0x00000002,
    (void *)func_ov001_02073894,
};

u32 data_ov001_0209edd8[7] = {
    0x0000001E, 0x00000A20, 0x00000060, 0x00000016,
    0x00000A80, 0x00000060, 0x00000016,
};

u32 data_ov001_0209edd4[1] = {
    0x000001C0,
};
