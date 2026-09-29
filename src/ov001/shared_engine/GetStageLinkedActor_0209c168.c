#include "nitro/types.h"

typedef struct RecordTable RecordTable;

typedef struct {
    u8 pad_00[0x18d94];
    RecordTable *linkedActorTable;
} StageManager;

extern StageManager *g_stageManager_020a0508;

extern void *func_ov001_0208f258(RecordTable *table, u32 id);

void *GetStageLinkedActor_0209c168(u32 id)
{
    if (g_stageManager_020a0508 != 0) {
        return func_ov001_0208f258(g_stageManager_020a0508->linkedActorTable, id);
    }
    return 0;
}
