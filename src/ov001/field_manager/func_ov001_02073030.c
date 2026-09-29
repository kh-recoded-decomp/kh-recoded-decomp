#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x5c8];
    s32 unk_5c8;
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;

extern u32 func_ov001_0207b3cc(void);
extern void func_ov001_0206ed30(FieldManager *manager);

void func_ov001_02073030(s32 value)
{
    FieldManager *manager = data_ov001_020a04a4.manager;

    if (value != 0 && manager->unk_5c8 == 0 && func_ov001_0207b3cc() == 0) {
        func_ov001_0206ed30(manager);
    }
    manager->unk_5c8 = value;
}
