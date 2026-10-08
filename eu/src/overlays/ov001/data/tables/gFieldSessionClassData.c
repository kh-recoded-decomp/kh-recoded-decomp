#include "nitro/types.h"

#pragma explicit_zero_data on

extern void func_ov001_02061468(void);
extern void ShutdownFieldSession(void);

#define InitFieldSession func_ov001_02061468

u32 gSessionStateOverlayIds[13] = {
    0x0000001C, 0x00000016, 0x0000001C, 0x0000001D,
    0x0000001E, 0x00000021, 0x00000023, 0x0000001F,
    0x00000024, 0x00000025, 0x00000020, 0x00000022,
    0x00000026,
};

s32 gFollowerOffsets[6] = {
    0x00000800, 0x00000000, 0x00000800, -0x00000800,
    0x00000000, 0x00000800,
};

void *gFieldSessionClassDescriptor[5] = {
    (void *)0x00020008,
    (void *)InitFieldSession,
    (void *)ShutdownFieldSession,
    (void *)0x000029BC,
    NULL,
};
