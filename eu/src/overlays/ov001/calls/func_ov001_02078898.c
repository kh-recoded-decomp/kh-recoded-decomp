#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xEC];
    s32 unk_EC;
    u8 pad_0F0[0x14];
    s32 unk_104;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04d0;

s32 func_ov001_02078898(void)
{
    FieldMenu *menu = data_ov001_020a04d0.menu;

    if (menu->unk_104 != 2) {
        return -1;
    }
    return menu->unk_EC;
}
