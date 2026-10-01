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
extern VecFx32 *func_ov001_0206dc4c(u32 index);

void SyncStageEntryPosition_02098fbc(u32 id, VecFx32 *outPosition)
{
    u32 index = (id - 1) & 0xffff;

    *outPosition = data_02053438;
    if (g_stageManager_020a0508 == NULL || outPosition == NULL) {
        return;
    }
    if (id != 0) {
        if (index >= 3) {
            return;
        }
        if (func_ov001_0206dc38() > 0) {
            g_stageManager_020a0508->entries[index].position = *func_ov001_0206dc4c(index);
        }
    }
    *outPosition = g_stageManager_020a0508->entries[index].position;
}
