#include "nitro/types.h"

extern void ClearTileRect(void);
extern void CopyTileRect(void);

const u32 data_ov045_020c07dc[9] = {
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000,
};

void *const data_ov045_020c07c8[5] = {
    (void *)0x00000003,
    (void *)0x00000001,
    (void *)0x00000003,
    (void *)CopyTileRect,
    (void *)ClearTileRect,
};
