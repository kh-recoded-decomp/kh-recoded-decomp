#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOv029OverlayState(void);
extern void ShutdownOv029SoundCtx(void);

void *data_ov029_020bab84[5] = {
    (void *)0x0002000E,
    (void *)InitOv029OverlayState,
    (void *)ShutdownOv029SoundCtx,
    (void *)0x00000018,
    NULL,
};

u32 data_ov029_020bab80[1] = {
    0xFFFFFFFF,
};
