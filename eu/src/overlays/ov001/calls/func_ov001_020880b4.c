#include "nitro/types.h"

extern u8 *GetStageEventRecord(u32 id);
extern void SetGroupAnimationTrack(u8 *record, s32 layer, s16 animationId, s32 option, BOOL persistent);

void func_ov001_020880b4(u32 id, s32 layer, s32 animationId, s32 option, BOOL persistent)
{
    u8 *record = GetStageEventRecord(id);

    if (record != NULL) {
        SetGroupAnimationTrack(record, layer, animationId, option, persistent);
    }
}
