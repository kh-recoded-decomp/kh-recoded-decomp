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
extern char data_020cf1d8[];

void InvokeFieldModeOp1d8_02072e38(void)
{
    ((void (*)(void *))data_020cf1d8)(data_ov001_020a04a4.manager->modeState);
}

