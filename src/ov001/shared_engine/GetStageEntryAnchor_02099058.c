#include "nitro/types.h"
#include "nitro/fx_types.h"

typedef struct StageEntry {
    u8 pad_00[0x10];
    VecFx32 position;
    u8 pad_1C[0x4];
} StageEntry;

typedef struct StageManager {
    u8 pad_00000[0x18a94];
    StageEntry entries[1];
} StageManager;

extern const VecFx32 data_02053438;
extern StageManager *g_stageManager_020a0508;
extern s32 func_ov001_0206dc38(void);
extern VecFx32 *func_ov001_0206dc60(u32 index);

void GetStageEntryAnchor_02099058(u32 id, VecFx32 *outPosition)
{
    u32 index;

    *outPosition = data_02053438;
    index = (id - 1) & 0xffff;
    if (g_stageManager_020a0508 == NULL || outPosition == NULL) {
        return;
    }
    *outPosition = g_stageManager_020a0508->entries[index].position;
    outPosition->y += 0x99a;
    if (id == 0) {
        return;
    }
    if (index >= 3) {
        return;
    }
    if (func_ov001_0206dc38() <= 0) {
        return;
    }
    *outPosition = *func_ov001_0206dc60(index);
}
