#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x1334];
    u32 unk_1334;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle gFieldSceneGlobals;

u32 GetFieldSceneLocationName(void)
{
    return gFieldSceneGlobals.manager->unk_1334;
}
