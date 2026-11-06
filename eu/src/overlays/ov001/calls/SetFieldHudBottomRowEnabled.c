#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x5c8];
    s32 unk_5c8;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle gFieldSceneGlobals;

extern u32 GetLoadedSubsceneMode(void);
extern void LoadFieldBottomRowTiles(FieldManager *manager);

void SetFieldHudBottomRowEnabled(s32 value)
{
    FieldManager *manager = gFieldSceneGlobals.manager;

    if (value != 0 && manager->unk_5c8 == 0 && GetLoadedSubsceneMode() == 0) {
        LoadFieldBottomRowTiles(manager);
    }
    manager->unk_5c8 = value;
}
