#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroySceneState(void);
extern void InitSceneOverlayState(void);

void *data_ov032_020bffe4[5] = {
    (void *)0x0002000E,
    (void *)InitSceneOverlayState,
    (void *)DestroySceneState,
    (void *)0x00000050,
    NULL,
};

u32 data_ov032_020bffe0[1] = {
    0xFFFFFFFF,
};
