#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x1338];
    u32 unk_1338;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04c4;

u32 func_ov001_02073060(void)
{
    return data_ov001_020a04c4.manager->unk_1338;
}
