#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0xb34];
    u32 handles[0x200];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

u32 GetFieldHandle_0207365c(s32 handleIndex)
{
    FieldManager *manager = data_ov001_020a04a4.manager;

    if (manager == NULL || handleIndex >= 0x200) {
        return 0;
    }
    return manager->handles[handleIndex];
}
