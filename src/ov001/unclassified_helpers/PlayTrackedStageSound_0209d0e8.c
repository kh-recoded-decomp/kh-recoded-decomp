#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct {
    u16 seqArcId;
    u16 soundId;
    u32 handle;
} StageSoundSlot;

typedef struct {
    u8 pad_00[0x18b78];
    StageSoundSlot soundSlots[64];
    u8 pad_18d78[0x18df0 - 0x18d78];
    u16 soundCursor;
} StageManager;

extern StageManager *g_stageManager_020a0508;
extern u32 PlayStageSoundAt_0209d080(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags);

u8 PlayTrackedStageSound_0209d0e8(s32 seqArcId, s32 soundId, VecFx32 *position, u32 flags)
{
    u32 handle;
    u8 attempt;
    StageSoundSlot *slot;

    handle = PlayStageSoundAt_0209d080(seqArcId, soundId, position, flags);
    if (handle != 0) {
        for (attempt = 0; attempt < 64; attempt++) {
            slot = &g_stageManager_020a0508->soundSlots[g_stageManager_020a0508->soundCursor];
            if (slot->handle == 0) {
                slot->handle = handle;
                slot->seqArcId = seqArcId;
                slot->soundId = soundId;
                return g_stageManager_020a0508->soundCursor + 1;
            }
            g_stageManager_020a0508->soundCursor = (g_stageManager_020a0508->soundCursor + 1) % 64;
        }
    }
    return 0;
}
