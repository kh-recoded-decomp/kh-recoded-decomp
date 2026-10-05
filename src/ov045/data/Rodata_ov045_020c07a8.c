#include "nitro/types.h"

extern void ClearTileRect_020c01ac(void);
extern void CopyTileRect_020c0118(void);

const u32 data_ov045_020c07bc[9] = {
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000, 0x00000000, 0x00000000, 0x00000000,
    0x00001000,
};

void *const data_ov045_020c07a8[5] = {
    (void *)0x00000003,
    (void *)0x00000001,
    (void *)0x00000003,
    (void *)CopyTileRect_020c0118,
    (void *)ClearTileRect_020c01ac,
};
