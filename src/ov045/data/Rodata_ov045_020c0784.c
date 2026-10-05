#include "nitro/types.h"

extern void ClearTileRect_020c01ac(void);
extern void CopyTileRect_020c0118(void);

void *const data_ov045_020c0794[5] = {
    (void *)0x0000002B,
    (void *)0x00000002,
    (void *)0x00000001,
    (void *)CopyTileRect_020c0118,
    (void *)ClearTileRect_020c01ac,
};

const u16 data_ov045_020c0784[8] = {
    18, 18, 10, 2, 352, 0, 0, 0,
};
