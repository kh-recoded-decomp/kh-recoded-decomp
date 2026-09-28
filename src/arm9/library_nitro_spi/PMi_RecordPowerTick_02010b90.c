#include "nitro/types.h"

typedef struct {
    u8 pad_00[8];
    u32 lastPowerTick;
} PMPowerState;

extern PMPowerState data_020597c0;
extern u32 data_02fffc3c;

void PMi_RecordPowerTick_02010b90(void)
{
    data_020597c0.lastPowerTick = data_02fffc3c;
}
