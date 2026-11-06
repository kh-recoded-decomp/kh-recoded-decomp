#include "nitro/types.h"

extern void BlitBoardWidgetAndFinishPendingTeardown(void);
extern void ClearBoardWidgetTileArea(void);

const u32 data_ov024_020b7384[8] = {
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x00000000,
    0xFFFFFFFF, 0xFFFFFFFF, 0x00000000, 0xFFFFFFFF,
};

void *const gBoardBackgroundContainerConfig[5] = {
    (void *)0x00000008,
    NULL,
    (void *)0x00000008,
    (void *)BlitBoardWidgetAndFinishPendingTeardown,
    (void *)ClearBoardWidgetTileArea,
};

const u32 gBoardObjectManagerConfig[4] = {
    0x00000000, 0x00000002, 0x00000000, 0x00000000,
};
