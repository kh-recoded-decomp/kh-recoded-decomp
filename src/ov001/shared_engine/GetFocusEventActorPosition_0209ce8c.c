#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEventRecord {
    u8 pad_00[0x10];
    u16 actorId;
} StageEventRecord;

typedef struct StageActor {
    u8 pad_000[0x2c0];
    VecFx32 position;
} StageActor;

typedef struct StageManager {
    u8 pad_00000[0x18f48];
    u16 focusEventId;
} StageManager;

extern StageManager *g_stageManager_020a0508;

extern StageActor *GetStageActor_0209c040(int id);
extern StageEventRecord *GetStageEventRecord_0209c0ec(u32 id);

BOOL GetFocusEventActorPosition_0209ce8c(VecFx32 *out)
{
    StageEventRecord *record;
    StageActor *actor;

    if (g_stageManager_020a0508->focusEventId == 0) {
        return FALSE;
    }
    record = GetStageEventRecord_0209c0ec(g_stageManager_020a0508->focusEventId);
    if (record == NULL) {
        return FALSE;
    }
    if (record->actorId == 0) {
        return FALSE;
    }
    actor = GetStageActor_0209c040((s16)record->actorId);
    if (actor == NULL) {
        return FALSE;
    }
    if (out != NULL) {
        *out = actor->position;
    }
    return TRUE;
}
