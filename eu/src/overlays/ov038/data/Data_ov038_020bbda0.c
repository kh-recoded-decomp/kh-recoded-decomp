#include "nitro/types.h"

#pragma explicit_zero_data on

extern void StartOv038SoundCtx(void);
extern void ShutdownOv038SoundCtx(void);

void *gResultsSoundContextConfig[5] = {
    (void *)0x0002000E,
    (void *)StartOv038SoundCtx,
    (void *)ShutdownOv038SoundCtx,
    (void *)0x00000018,
    NULL,
};

u32 gResultsObjectHandle[1] = {
    0xFFFFFFFF,
};
