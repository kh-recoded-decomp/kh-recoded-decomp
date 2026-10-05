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
extern void func_020cf150(void *state);

void InvokeFieldModeOp150_02072e08(void)
{
    func_020cf150(data_ov001_020a04a4.manager->modeState);
}
