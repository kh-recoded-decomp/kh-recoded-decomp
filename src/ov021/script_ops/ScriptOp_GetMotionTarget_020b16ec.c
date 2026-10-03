#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u8 pad_00[0x34];
    VecFx32 vector;
} ScriptContext;

typedef struct {
    u32 unk_00;
    VecFx32 anchor;
    u8 pad_10[0xc];
    VecFx32 target;
} MotionRecord;

typedef struct {
    u8 pad_00[0x16];
    u16 motionId;
} ScriptOwner;

extern ScriptOwner *data_ov021_020b56a4;

extern MotionRecord *GetStageMotionRecord_0209c18c(u32 id);

int ScriptOp_GetMotionTarget_020b16ec(ScriptContext *context) {
    MotionRecord *record = GetStageMotionRecord_0209c18c(data_ov021_020b56a4->motionId);

    if (record != NULL) {
        context->vector = record->target;
    }
    return 0;
}
