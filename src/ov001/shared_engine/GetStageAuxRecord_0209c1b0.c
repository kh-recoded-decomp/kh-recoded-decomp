#include "nitro/types.h"

typedef struct RecordTable RecordTable;

typedef struct {
    u8 pad_00[0x18d9c];
    RecordTable *auxTable;
} StageManager;

extern StageManager *g_stageManager_020a0508;

extern void *func_ov001_0208f258(RecordTable *table, u32 id);

void *GetStageAuxRecord_0209c1b0(u32 id)
{
    if (g_stageManager_020a0508 != 0) {
        return func_ov001_0208f258(g_stageManager_020a0508->auxTable, id);
    }
    return 0;
}
