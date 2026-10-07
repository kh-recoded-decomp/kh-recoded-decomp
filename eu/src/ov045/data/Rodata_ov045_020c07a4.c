#include "nitro/types.h"

extern void ClearTileRect(void);
extern void CopyTileRect(void);

void *const data_ov045_020c07b4[5] = {
    (void *)0x0000002B,
    (void *)0x00000002,
    (void *)0x00000001,
    (void *)CopyTileRect,
    (void *)ClearTileRect,
};

const u16 data_ov045_020c07a4[8] = {
    18, 18, 10, 2, 352, 0, 0, 0,
};
