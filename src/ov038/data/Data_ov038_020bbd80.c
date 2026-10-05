#include "nitro/types.h"

#pragma explicit_zero_data on

extern void ShutdownOv038SoundCtx_020ba4c8(void);
extern void StartOv038SoundCtx_020ba3e0(void);

void *data_ov038_020bbd84[5] = {
    (void *)0x0002000E,
    (void *)StartOv038SoundCtx_020ba3e0,
    (void *)ShutdownOv038SoundCtx_020ba4c8,
    (void *)0x00000018,
    NULL,
};

u32 data_ov038_020bbd80[1] = {
    0xFFFFFFFF,
};
