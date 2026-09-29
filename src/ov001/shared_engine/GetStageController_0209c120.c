#include "nitro/types.h"

typedef struct RecordTable RecordTable;

typedef struct {
    u8 pad_00[0x18d88];
    RecordTable *controllerTable;
} StageManager;

extern StageManager *g_stageManager_020a0508;

extern void *func_ov001_0208f258(RecordTable *table, u32 id);

void *GetStageController_0209c120(u32 id)
{
    if (g_stageManager_020a0508 != 0) {
        return func_ov001_0208f258(g_stageManager_020a0508->controllerTable, id);
    }
    return 0;
}
