#include "nitro/types.h"

#pragma explicit_zero_data on

extern void DestroySceneState_020ba804(void);
extern void InitSceneOverlayState_020ba3e0(void);

void *data_ov032_020bffc4[5] = {
    (void *)0x0002000E,
    (void *)InitSceneOverlayState_020ba3e0,
    (void *)DestroySceneState_020ba804,
    (void *)0x00000050,
    NULL,
};

u32 data_ov032_020bffc0[1] = {
    0xFFFFFFFF,
};
