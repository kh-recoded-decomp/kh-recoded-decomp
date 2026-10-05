#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ShutdownFieldSession_02061b54(void);
extern void func_ov001_02061468(void);

u32 data_ov001_0209e64c[13] = {
    0x0000001C, 0x00000016, 0x0000001C, 0x0000001D,
    0x0000001E, 0x00000021, 0x00000023, 0x0000001F,
    0x00000024, 0x00000025, 0x00000020, 0x00000022,
    0x00000026,
};

u32 data_ov001_0209e634[6] = {
    0x00000800, 0x00000000, 0x00000800, 0xFFFFF800,
    0x00000000, 0x00000800,
};

void *data_ov001_0209e620[5] = {
    (void *)0x00020008,
    (void *)func_ov001_02061468,
    (void *)ShutdownFieldSession_02061b54,
    (void *)0x000029BC,
    NULL,
};
