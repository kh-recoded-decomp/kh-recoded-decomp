#include "nitro/types.h"

extern u8 *GetStageEventRecord_0209c0ec(u32 id);
extern void func_ov001_02097994(u8 *record, s32 layer, s16 animationId, s32 option, BOOL persistent);

void func_ov001_0208808c(u32 id, s32 layer, s32 animationId, s32 option, BOOL persistent)
{
    u8 *record = GetStageEventRecord_0209c0ec(id);

    if (record != NULL) {
        func_ov001_02097994(record, layer, animationId, option, persistent);
    }
}
