#include "nitro/types.h"

#pragma explicit_zero_data on

extern void InitOverlayObjectSystem_02088250(void);
extern void ShutdownOverlayObjectSystem_020884b0(void);

void *data_ov001_0209f2cc[5] = {
    (void *)0x000D0010,
    (void *)InitOverlayObjectSystem_02088250,
    (void *)ShutdownOverlayObjectSystem_020884b0,
    (void *)0x00003F20,
    NULL,
};

u32 data_ov001_0209f2c8[1] = {
    0xFFFFFFFF,
};
