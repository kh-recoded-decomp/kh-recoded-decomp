#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 unk_C8;
    u8 pad_0CC[0x78];
    s32 unk_144;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern BOOL func_ov001_02072040(void);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL func_ov001_0207531c(void);

BOOL func_ov001_02077bd8(void)
{
    FieldMenu *menu;

    if (func_ov001_02072040()) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear_0207259c()) {
        return FALSE;
    }
    if (func_ov001_0207531c()) {
        return FALSE;
    }
    menu = data_ov001_020a04b0.menu;
    if (menu->unk_C8 >= 2 && menu->unk_144 < 0) {
        menu->unk_144 = 0;
    }
    return TRUE;
}
