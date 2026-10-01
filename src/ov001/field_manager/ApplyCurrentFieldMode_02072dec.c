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
extern int func_ov001_020789b8(void);
extern void func_020cf0b4(void *state, int mode);

void ApplyCurrentFieldMode_02072dec(void)
{
    int mode = func_ov001_020789b8();

    func_020cf0b4(data_ov001_020a04a4.manager->modeState, mode);
}
