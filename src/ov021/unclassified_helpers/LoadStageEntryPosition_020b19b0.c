#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageInfo {
    u8 pad_000[0x28c];
    u16 low : 11;
    u16 entryId : 3;
    u16 high : 2;
} StageInfo;

typedef struct StageContext {
    u8 pad_00[8];
    StageInfo *info;
} StageContext;

extern StageContext data_ov021_020b56a4;
extern void GetStageEntryPosition_020992ac(u32 id, VecFx32 *outPosition);

int LoadStageEntryPosition_020b19b0(u8 *actor)
{
    GetStageEntryPosition_020992ac(data_ov021_020b56a4.info->entryId, (VecFx32 *)(actor + 0x34));
    return 0;
}
