#include "nitro/types.h"

typedef struct MenuEntry {
    u8 pad_00[0x8];
    s32 value;
    u8 pad_0C[0x1C];
    u16 flags;
    u16 unk_2A;
} MenuEntry;

typedef struct FieldMenu {
    u8 pad_000[0xEC];
    s32 cursor;
    u8 pad_0F0[0x4];
    s32 unk_F4;
    u8 pad_0F8[0x4];
    s32 unk_FC;
    u8 pad_100[0x4];
    s32 unk_104;
    u8 pad_108[0x30];
    s32 unk_138;
} FieldMenu;

typedef struct FieldMenuHandle {
    u32 unk_00;
    FieldMenu *menu;
} FieldMenuHandle;

extern FieldMenuHandle data_ov001_020a04b0;

extern MenuEntry *func_ov001_02075348(FieldMenu *menu, s32 index, s32 arg2, s32 arg3);
extern BOOL IsModeSetOrFlag370aClear_0207259c(void);
extern BOOL IsHudFlag7Set_020725bc(void);
extern BOOL IsFieldFlag10Set_020728c4(void);

s32 GetSelectedMenuEntryValue_02077f80(void)
{
    FieldMenu *menu = data_ov001_020a04b0.menu;
    MenuEntry *entry;
    s32 result = -1;

    if (menu->unk_138 == 0) {
        return result;
    }
    if (menu->unk_104 == 2) {
        return menu->unk_F4;
    }
    if (menu->unk_FC != 0) {
        return result;
    }
    entry = func_ov001_02075348(menu, menu->cursor, 1, 0);
    if ((entry->flags & 1) && (entry->flags & 4)) {
        if (!IsModeSetOrFlag370aClear_0207259c() || IsHudFlag7Set_020725bc() || IsFieldFlag10Set_020728c4()) {
            if (entry->unk_2A != 0) {
                result = entry->value;
            }
        } else {
            result = entry->value;
        }
    }
    return result;
}
