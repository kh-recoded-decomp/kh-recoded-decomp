#include "nitro/types.h"

typedef struct {
    u8 pad_000[0x118];
    s32 unk_118;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

void func_ov001_02078938(s32 value)
{
    data_ov001_020a04b0.menu->unk_118 = value;
}
