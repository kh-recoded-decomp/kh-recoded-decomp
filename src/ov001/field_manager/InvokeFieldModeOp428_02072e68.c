#include "nitro/types.h"

typedef struct FieldManager {
    u8 pad_000[0x2f4];
    u8 modeState[4];
} FieldManager;

typedef struct FieldManagerHandle {
    u32 unk_00;
    FieldManager *manager;
} FieldManagerHandle;

extern FieldManagerHandle data_ov001_020a04a4;
extern void func_020cf428(void *state);

void InvokeFieldModeOp428_02072e68(void)
{
    func_020cf428(data_ov001_020a04a4.manager->modeState);
}

