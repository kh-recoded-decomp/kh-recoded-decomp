#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x1338];
    u32 unk_1338;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle gFieldSceneGlobals;

u32 GetFieldSceneEntryListRecord(void)
{
    return gFieldSceneGlobals.manager->unk_1338;
}
