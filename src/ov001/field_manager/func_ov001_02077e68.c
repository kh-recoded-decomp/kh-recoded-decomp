#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 entryCount;
    u8 pad_0CC[0x20];
    s32 cursorIndex;
    s32 prevCursorIndex;
    u8 pad_0F4[0x8];
    s32 state;
    u8 pad_100[0x8];
    s32 unk_108;
    u8 pad_10C[0x2C];
    s32 unk_138;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL func_ov001_020728c4(void);
extern BOOL func_ov001_0207531c(void);
extern void *func_ov001_02075348(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);

BOOL func_ov001_02077e68(void)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;

    if (menu->unk_138 == 0) {
        return FALSE;
    }
    if (menu->state != 0) {
        return FALSE;
    }
    if (menu->entryCount < 2) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear_0207259c() || IsHudFlag7Set_020725bc() || func_ov001_020728c4()) {
        return FALSE;
    }
    if (func_ov001_0207531c()) {
        return FALSE;
    }
    menu->state = 2;
    menu->unk_108 = 0;
    menu->prevCursorIndex = menu->cursorIndex;
    func_ov001_02075348(menu, menu->cursorIndex, 2, &menu->cursorIndex);
    return TRUE;
}
