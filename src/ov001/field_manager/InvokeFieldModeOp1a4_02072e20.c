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
extern void func_020cf1a4(void *state, int value);

void InvokeFieldModeOp1a4_02072e20(int value)
{
    func_020cf1a4(data_ov001_020a04a4.manager->modeState, value);
}

