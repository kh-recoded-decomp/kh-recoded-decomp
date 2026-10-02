#include "nitro/types.h"

typedef struct {
    u8 pad_000[0xC8];
    s32 entryCount;
    u8 pad_0CC[0x8];
    s32 subMode;
    u8 pad_0D8[0x14];
    s32 cursorIndex;
    u8 pad_0F0[0xC];
    s32 state;
    s32 transition;
    u8 pad_104[0x4];
    s32 timer;
    u8 pad_10C[0x28];
    s32 pendingConfirm;
    s32 active;
} FieldMenu;

typedef struct {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

typedef struct {
    u8 pad_00[0x2C];
    s32 enabled;
} FieldMenuEntry;

typedef struct {
    u8 pad[0x2878];
    u32 unk0 : 18;
    u32 menuMode : 2;
} GameState;

extern FieldMenuHandle data_ov001_020a04b0;
extern GameState *data_0205fe0c;

extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);
extern BOOL IsLeadEntryFlag80Set_0207531c(void);
extern FieldMenuEntry *func_ov001_02075348(FieldMenu *menu, s32 group, s32 slot, s32 *outIndex);
extern void func_ov001_02075d74(FieldMenu *menu, int alternate);
extern BOOL func_ov001_02077ef4(void);

BOOL FieldMenu_TryOpenByMode_02077d64(void) {
    FieldMenu *menu = data_ov001_020a04b0.menu;
    FieldMenuEntry *entry = func_ov001_02075348(menu, menu->cursorIndex, 1, NULL);

    if (menu->active == 0) {
        return FALSE;
    }
    if (menu->state != 0) {
        return FALSE;
    }
    if (!IsModeSetOrFlag370aClear_0207259c()) {
        return FALSE;
    }
    if (IsLeadEntryFlag80Set_0207531c()) {
        return FALSE;
    }
    switch (data_0205fe0c->menuMode) {
    case 0:
        if (menu->entryCount < 2) {
            return FALSE;
        }
        if (!IsModeSetOrFlag370aClear_0207259c() || IsHudFlag7Set_020725bc() || IsFieldFlag10Set_020728c4()) {
            return FALSE;
        }
        func_ov001_02075d74(menu, TRUE);
        menu->state = TRUE;
        menu->transition = 2;
        menu->timer = 0;
        return TRUE;
    case 2:
    default:
        func_ov001_02075d74(menu, TRUE);
        menu->state = TRUE;
        menu->transition = 0;
        menu->timer = 0;
        return FALSE;
    case 1:
        switch (menu->subMode) {
        case 0:
            return FALSE;
        case 1:
            if (entry->enabled == 0) {
                return FALSE;
            }
            break;
        }
        menu->pendingConfirm = 1;
        return func_ov001_02077ef4();
    }
}
