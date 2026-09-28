#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xFC];
    s32 state;
    u8 pad_100[0x38];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL func_ov001_0207531c(void);
extern BOOL func_ov001_02075db8(FieldMenu *menu);

BOOL func_ov001_02077ef4(void)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;

    if (menu->unk_138 == 0) {
        return FALSE;
    }
    if (menu->state != 0) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear_0207259c()) {
        return FALSE;
    }
    if (func_ov001_0207531c()) {
        return FALSE;
    }
    return func_ov001_02075db8(menu);
}
