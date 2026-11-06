#include "nitro/types.h"

extern void ClearTileRect(void);
extern void CopyTileRect(void);

void *const gBattleGaugeBackgroundConfig[5] = {
    (void *)0x0000002B,
    (void *)0x00000002,
    (void *)0x00000001,
    (void *)CopyTileRect,
    (void *)ClearTileRect,
};

const u16 gBattleGaugeTextFrame[8] = {
    18, 18, 10, 2, 352, 0, 0, 0,
};
