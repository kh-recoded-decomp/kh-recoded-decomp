#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv029OverlayState_020ba3e0(void);
extern void ShutdownOv029SoundCtx_020ba52c(void);

void *data_ov029_020bab64[5] = {
    (void *)0x0002000E,
    (void *)InitOv029OverlayState_020ba3e0,
    (void *)ShutdownOv029SoundCtx_020ba52c,
    (void *)0x00000018,
    NULL,
};

u32 data_ov029_020bab60[1] = {
    0xFFFFFFFF,
};
